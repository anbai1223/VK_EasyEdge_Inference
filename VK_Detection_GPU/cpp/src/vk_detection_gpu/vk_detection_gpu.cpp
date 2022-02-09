/***************************************************************************
 *
 * Copyright (c) 2021 VK, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @author VK
 * @brief SDK vk_easyedge_inference
 *
 **/
#include <atomic>
#include <assert.h>
#include <chrono>
#include <iostream>
#include <signal.h>
#include <sstream>

#include "easyedge/easyedge.h"
#include "easyedge/easyedge_config.h"
#include "easyedge/easyedge_gpu_turbo_config.h"
#include "easyedge_video_decoding.h"
#include "vision_proc.h"

using namespace easyedge;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <time.h>
#include <string>
#include "vkbg.h"


std::atomic<bool> quit(false);

void signal_handler(int) {
    quit.store(true);
}



int main(int argc, char *argv[]) {
    /*
    参数1：RES路径
    参数2：video_type(视频文件：1，csi摄像头：2，usb摄像头：3)
    参数3：video_src(视频文件路径或摄像头设备号)
    参数4（可选）：serial_num(如果设置为空，SDK会自动寻找本地已经激活过的license)
    */
    if (argc < 4) {
        std::cerr << "Usage: ./vk_detection_gpu {res_dir} {video_type} {video_src} {serial_num}" << std::endl
                  << "       {res_dir}    : RES directory" << std::endl
                  << "       {video_type} : Video file->1, CSI camera->2, USB camera->3" << std::endl
                  << "       {video_src}  : Video file path or camera device id" << std::endl
                  << "       {serial_num} : is optional if this device has been activated" << std::endl;
        exit(-1);
    }
    std::string res_dir = argv[1];
    int video_type = std::atoi(argv[2]);
    std::string video_src = argv[3];
    std::string serial_num = "";

    if (argc >= 5) {
        serial_num = argv[4];
    }
  
    cv::Mat background;
    cv::Mat background_temp;
    background = vk_init();
    cv::Mat frame;
    cv::Mat imageROI;
    cv::VideoCapture cap;
    
    

    int device_id = std::atoi(video_src.c_str());
    std::stringstream csi_str; 
        
    csi_str << "nvarguscamerasrc sensor-id=" << device_id << " ! video/x-raw(memory:NVMM), width=320, height=180, format=NV12, framerate=30/1  ! nvvidconv flip-method=0 !  videoconvert ! video/x-raw, format=BGR ! appsink";
    
    if (video_type == 1) {
	      //open video file
        cap.open(video_src);
        if(cap.isOpened()) { // check if we succeeded
           std::cout << "Video file open" << std::endl; 
        }
        else {
           std::cout << "Video file open failed" << std::endl; 
        }
    }    
    
    else if (video_type == 2) {  
        //open csi camera
	      cap.open(csi_str.str());
        if(cap.isOpened()) { // check if we succeeded
           std::cout << "CSI camera open" << std::endl; 
        }
        else {
           std::cout << "CSI camera open failed" << std::endl; 
        }
    }
    else if (video_type == 3){
        //open usb camera
	      cap.open(device_id);
        if(cap.isOpened()) { // check if we succeeded
           std::cout << "USB camera open" << std::endl; 
        }
        else {
           std::cout << "USB camera open failed" << std::endl; 
        }
    }


    struct sigaction sa;
    memset( &sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);


    EdgePredictorConfig config;
    config.model_dir = res_dir;
    // 在这里设置序列号 或者 通过环境变量 EDGE_PREDICTOR_KEY_SERIAL_NUM 设置序列号
    // 如果设置为空，SDK会自动寻找本地已经激活过的license
    if (!serial_num.empty()) {
        config.set_config(params::PREDICTOR_KEY_SERIAL_NUM, serial_num);
    }
    config.set_config(params::PREDICTOR_KEY_DEVICE_ID, 0);              // 设置需要使用的GPU
    config.set_config(params::PREDICTOR_KEY_GTURBO_MAX_BATCH_SIZE, 1);  // 优化的模型可以支持的最大batch_size，实际单次推理的图片数不能大于此值
    config.set_config(params::PREDICTOR_KEY_GTURBO_MAX_CONCURRENCY, 1); // 设置device对应的卡可以使用的最大线程数
    config.set_config(params::PREDICTOR_KEY_GTURBO_FP16, false);        // 置true开启fp16模式推理会更快，精度会略微降低，但取决于硬件是否支持fp16，不是所有模型都支持fp16，参阅文档
    config.set_config(params::PREDICTOR_KEY_GTURBO_COMPILE_LEVEL, 1);   // 编译模型的策略，如果当前设置的max_batch_size与历史编译存储的不同，则重新编译模型

    // 创建predictor并初始化
    auto predictor = global_controller()->CreateEdgePredictor(config);
    if (predictor->init() != EDGE_OK) {
        exit(-1);
    }

    


    cv::namedWindow("vkrobot",cv::WINDOW_NORMAL);
    cv::resizeWindow("vkrobot",640,480);
    
    
    std::vector<EdgeResultData> results;
    while (true) {
        background.copyTo(background_temp);
        
        results.clear();
        clock_t start = clock();

        cap.read(frame);
        
        // 垂直翻转
        //cv::flip(frame,frame,0);
        
        predictor->infer(frame, results);
        // 应用识别结果到frame
        render(frame, results, predictor->model_info().kind);

	      clock_t end = clock();
	      auto gap = (double)(end - start) / CLOCKS_PER_SEC;
	      std::cout << "起始时间：" << (double)(start)/CLOCKS_PER_SEC << std::endl;
	      std::cout << "结束时间：" << (double)(end)/ CLOCKS_PER_SEC << std::endl;
	      std::cout << "时间间隔为：" << gap << std::endl;
        
        
        cv::resize(frame,frame,cv::Size(1080,720));
        imageROI = background_temp(cv::Rect(670, 207, frame.cols, frame.rows));
        
        
        // 显示识别结果
        if (!results.empty()){
          for (int i = 0; i < results.size(); i++){
            if ( i > 6) { //最多显示7条结果
              break;
            }
          
            //置信度保留两位小数
            std::stringstream prob;
            prob << std::fixed << std::setprecision(2) << results[i].prob; 
            
            cv::putText(background_temp,std::to_string(i+1) + "  " + results[i].label, cv::Point(150,300 + i *95),cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255,245,0), 2, 1);
            cv::putText(background_temp,"probability: " + prob.str(), cv::Point(200,330 + i *95),cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0,255,255), 2, 1);
          }
        }
        else {
            cv::putText(background_temp, "empty result", cv::Point(200,300),cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255,255,255), 2, 1);
        }
        
        
        // 获取系统当前时间
        std::stringstream local_time;
        std::time_t tt;
        std::time(&tt);
        tt = tt + 8*3600; //transform the time zone
        struct tm* t1 = std::gmtime(&tt);
        
        local_time << t1->tm_year + 1900 << "-" << t1->tm_mon + 1 << "-" << t1->tm_mday << " " << t1->tm_hour << ":" << t1->tm_min << ":" << t1->tm_sec;
        // 显示当前时间
        cv::putText(background_temp, local_time.str(), cv::Point(120,1040),cv::FONT_HERSHEY_COMPLEX, 1.2, cv::Scalar(255,255,255), 2, 1);
        std::cout << local_time.str() << std::endl;
        
        
        // 将每帧复制到背景的ROI中
        frame.copyTo(imageROI);
      	cv::imshow("vkrobot",background_temp);       
        
        if ((cv::waitKey(1) & 0xff) == 27) break;
        
        if (quit.load()) {
          cap.release();
          break;
        }
    }

    std::cout << "Done" << std::endl;
    return 0;
}
