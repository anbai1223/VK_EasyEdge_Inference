/***************************************************************************
 *
 * Copyright (c) 2021 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @author Baidu
 * @brief video encoding
 *
 **/
#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "easyedge.h"
#include "easyedge_video.h"

extern "C" {  
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
}

#ifndef EASYEDGE_VIDEOIO_PUBLIC_API
#define EASYEDGE_VIDEOIO_PUBLIC_API
#endif

namespace easyedge {

class VideoEncoding;

EASYEDGE_VIDEOIO_PUBLIC_API std::unique_ptr<VideoEncoding> CreateVideoEncoding();

class VideoEncoding {
public:
    VideoEncoding() = default;

    VideoEncoding(const VideoEncoding&) = delete;

    VideoEncoding& operator=(const VideoEncoding&) = delete;

    VideoEncoding(VideoEncoding&&) = delete;

    VideoEncoding& operator=(VideoEncoding&&) = delete;

    virtual ~VideoEncoding() = default;

public:
    /**
     * @brief 对编码参数进行初始化
     * @param 
     * @return
     */
    virtual int init(const char* url, const char* format, const char* encoder, int bit_rate, int w, int h, int fps) = 0;

    /**
     * @brief 对输入的图像编码生成视频流
     * @param
     * @return
     */    
    virtual int encode(cv::Mat rgb, int frame_count) = 0;
};

} // namespace easyedge