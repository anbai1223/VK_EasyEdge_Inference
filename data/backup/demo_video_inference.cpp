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


// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <time.h>
#include<iostream>
#include<string>
#include<time.h>



std::atomic<bool> quit(false);

void signal_handler(int) {
    quit.store(true);
}

int main(int argc, char *argv[]) {
    
    cv::VideoCapture cap("nvarguscamerasrc sensor-id=1 ! video/x-raw(memory:NVMM), width=416, height=416, format=NV12, framerate=30/1 ! nvvidconv flip-method=2 ! video/x-raw, width=416, height=416, format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink"); // open the default camera
   
    

    //cv::VideoCapture cap(2);
    if(cap.isOpened())  // check if we succeeded
       std::cout << "camera open" << std::endl;  
    
    cv::Mat frame;


    if (argc < 4) {
        std::cerr << "Usage: ./easyedge_video_inference {res_dir} {video_type} {video_src} {serial_num}" << std::endl
                  << "       {serial_num} is optional if this device has been activated" << std::endl;
        exit(-1);
    }
    std::string res_dir = argv[1];
    int video_type = std::atoi(argv[2]);
    std::string video_src = argv[3];
    std::string serial_num = "";

    if (argc >= 5) {
        serial_num = argv[4];
    }

    struct sigaction sa;
    memset( &sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // 日志打印相关配置
//    EdgeLogConfig log_config;
//    log_config.enable_debug = false;
//    global_controller()->set_log_config(log_config);

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

    FrameTensor frame_tensor;
    VideoConfig video_config;
    video_config.source_type = static_cast<SourceType>(video_type);
    video_config.source_value = video_src;
    video_config.skip_frames = 0;
    video_config.retrieve_all = true;
    video_config.enable_display = false;
    video_config.enable_save = true;
    video_config.save_path = video_src + ".result.mp4";
    video_config.save_all = true;

    //auto video_decoding = CreateVideoDecoding(video_config);
    //std::cout << "input fps: " << video_decoding->get_fps()
    //          << ", width: " << video_decoding->get_width()
    //          << ", height: " << video_decoding->get_height() << std::endl;


    cv::namedWindow("test",1);
    std::vector<EdgeResultData> results;
    //while (video_decoding->next(frame_tensor) == EDGE_OK) {
    while (true) {
        results.clear();
        clock_t start = clock();

	// 在retrieve_all模式下，会返回所有frame，以is_needed标志需要预测的frame
        //if (frame_tensor.is_needed) {
            //predictor->infer(frame_tensor.frame, results);
            cap.read(frame);
            predictor->infer(frame, results);
            // 应用识别结果到frame
            render(frame, results, predictor->model_info().kind);
        //}
        //video_decoding->display(frame_tensor);
        // 将frame存储为视频
        //video_decoding->save(frame_tensor);

	
	clock_t end = clock();
	auto gap = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "起始时间：" << (double)(start)/CLOCKS_PER_SEC << std::endl;
	std::cout << "结束时间：" << (double)(end)/ CLOCKS_PER_SEC << std::endl;
	std::cout << "时间间隔为：" << gap << std::endl;

	cv::imshow("test",frame);

	if (cv::waitKey(30) >= 0) break;

        if (quit.load()) {
            cap.release();
            break;
        }
    }

    std::cout << "Done" << std::endl;
    return 0;
}
