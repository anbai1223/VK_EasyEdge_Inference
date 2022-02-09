/***************************************************************************
 *
 * Copyright (c) 2021 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @author Baidu
 * @brief easyedge video header
 *
 **/
#pragma once

#include <cstdlib>
#include <map>
#include <string>
#include <vector>

#include "opencv2/opencv.hpp"

namespace easyedge {

/**
 * @brief 输入源类型
 */
enum class SourceType {
    kVideoFile = 1,                   // 本地视频文件
    kCameraId = 2,                    // 摄像头的index
    kNetworkStream = 3,               // 网络视频流
};

/**
 * @brief 帧数据结构
 */
struct FrameTensor {
    cv::Mat frame;                     // 帧数据
    int frame_id{0};                   // 该帧在源资源中的index
    bool is_needed{false};             // 标志该帧是否为根据skip_frames策略抽取到的所需要的帧
};

/**
 * @brief 输入源分辨率
 */
enum class Resolution {
    kAuto,
    k1080P,
    k720P,
    k480P,
    k360P,
    k240P,
};

/**
 * @brief 视频源、抽帧策略、存储策略的设置选项
 */
struct VideoConfig {
    SourceType source_type;            // 输入源类型
    std::string source_value;          // 输入源地址，如视频文件路径、摄像头index、网络流地址
    int skip_frames{0};                // 设置跳帧，每隔skip_frames帧抽取一帧，并把该抽取帧的is_needed置为true
    int retrieve_all{false};           // 是否抽取所有frame以便于作为显示和存储，对于不满足skip_frames策略的frame，把所抽取帧的is_needed置为false
    int input_fps{0};                  // 在采取抽帧之前设置视频的fps
    Resolution resolution{Resolution::kAuto}; // 采样分辨率，只对camera有效

    bool enable_display{false};
    std::string window_name{"EasyEdge"};
    bool display_all{false};           // 是否显示所有frame，若为false，仅显示根据skip_frames抽取的frame

    bool enable_save{false};
    std::string save_path;             // frame存储为视频文件的路径
    bool save_all{false};              // 是否存储所有frame，若为false，仅存储根据skip_frames抽取的frame

    std::map<std::string, std::string> conf;
};

} // namespace easyedge
