/***************************************************************************
 *
 * Copyright (c) 2021 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @author Baidu
 * @brief SDK demo_video_inference
 *
 **/

#include <atomic>
#include <chrono>
#include <iostream>
#include <sstream>
#include <signal.h>

#include "easyedge/easyedge.h"
#include "easyedge_video_decoding.h"
#include "vision_proc.h"

using namespace easyedge;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <time.h>
#include <string>
#include "vkbg.h"
#include <fstream>
#include <vector>

std::atomic<bool> quit(false);

void signal_handler(int) {
    quit.store(true);
}

struct Result_label {
    std::string label;
    int count;
};

std::vector<Result_label> get_label_vector(std::string label_path){
    std::ifstream label_file;
    label_file.open(label_path);
    std::vector<Result_label> label_vector;
    std::string s;
    while (std::getline(label_file, s)) {
        if (s == "[default]"){
            continue;
        }
        Result_label result_label;
        result_label.label = s;
        result_label.count = 0;
        label_vector.push_back(result_label);
    }
    label_file.close();
    return label_vector;
}


int main(int argc, char *argv[]) {
    /*
    参数1：RES路径
    参数2：video_type(视频文件：1，csi摄像头：2，usb摄像头：3)
    参数3：video_src(视频文件路径或摄像头设备号)
    参数4：confidence(置信度0~1，当不需要填参数5序列号时也可不填置信度，默认为0.0)
    参数5（可选）：serial_num(如果设置为空，SDK会自动寻找本地已经激活过的license)
    */
    if (argc < 4) {
        std::cerr << "Usage: ./vk_detection_arm {res_dir} {video_type} {video_src} {serial_num}" << std::endl
                  << "       {res_dir}    : RES directory" << std::endl
                  << "       {video_type} : Video file->1, CSI camera->2, USB camera->3" << std::endl
                  << "       {video_src}  : Video file path or camera device id" << std::endl
                  << "       {confidence} : is optional if you want to change confidence level,but the confidence level need to be between 0 and 1(default 0)" << std::endl
                  << "       {serial_num} : is optional if this device has been activated" << std::endl;
        exit(-1);
    }
    std::string res_dir = argv[1];
    int video_type = std::atoi(argv[2]);
    std::string video_src = argv[3];
    float confidence = 0.0;   //置信度参数
    std::string serial_num = "";

    if (argc >= 5) {
        confidence = std::atof(argv[4]);
        if (confidence < 0 || confidence > 1) {
            std::cerr << "The confidence level needs to be between 0 and 1" << std::endl;
            exit(-1);
        }
        
    }

    if (argc >= 6) {
        serial_num = argv[5];
    }
    std::cout << "confidence: " << confidence << std::endl;
    
    // 获取label_list.txt路径
    std::stringstream label_path;
    if (res_dir[res_dir.length()-1] == '/'){
        label_path << res_dir << "label_list.txt";
    }else {
        label_path << res_dir << "/label_list.txt";
    }
    
    //获取所有label
    std::vector<Result_label> label_vector = get_label_vector(label_path.str());
    
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
    
    
    
#ifdef WIN32
    signal(SIGINT,  signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGABRT, signal_handler);
#else
    struct sigaction sa;
    memset( &sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
#endif

    

    EdgePredictorConfig config;
    config.model_dir = res_dir;
    // 在这里设置序列号 或者 通过环境变量 EDGE_PREDICTOR_KEY_SERIAL_NUM 设置序列号
    // 如果设置为空，SDK会自动寻找本地已经激活过的license
    if (!serial_num.empty()) {
        config.set_config(params::PREDICTOR_KEY_SERIAL_NUM, serial_num);
    }

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
        
        // 将label数量清零
        for (int i = 0; i< label_vector.size(); i++) {
          label_vector[i].count = 0;
        }
        
        // 显示识别结果
        if (!results.empty()){
          for (int i = 0; i < results.size(); i++){

            if (results[i].prob >= confidence) {
                for (int j = 0; j < label_vector.size(); j++) {
                    if (label_vector[j].label == results[i].label) {
                        label_vector[j].count++;
                        break;
                    }
                }
            }
          
          }
          
          // 显示识别到的每个label的总数量
          for (int k = 0; k < label_vector.size(); k++) {
            if ( k > 6) { //最多显示7条结果
              break;
            }
            
            cv::putText(background_temp,std::to_string(k+1) + "  " + label_vector[k].label, cv::Point(150,300 + k * 95),cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255,245,0), 2, 1);
            cv::putText(background_temp,"sum: " + std::to_string(label_vector[k].count), cv::Point(200,330 + k * 95), cv:: FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0,255,255), 2, 1);
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