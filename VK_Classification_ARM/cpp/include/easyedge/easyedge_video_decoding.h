/***************************************************************************
 *
 * Copyright (c) 2021 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @author Baidu
 * @brief video decoding
 *
 **/
#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "easyedge.h"
#include "easyedge_video.h"

#ifndef EASYEDGE_VIDEOIO_PUBLIC_API
#define EASYEDGE_VIDEOIO_PUBLIC_API
#endif

namespace easyedge {

class VideoDecoding;

EASYEDGE_VIDEOIO_PUBLIC_API std::unique_ptr<VideoDecoding> CreateVideoDecoding(VideoConfig &video_config);

class VideoDecoding {
public:
    VideoDecoding() = default;

    VideoDecoding(const VideoDecoding&) = delete;

    VideoDecoding& operator=(const VideoDecoding&) = delete;

    VideoDecoding(VideoDecoding&&) = delete;

    VideoDecoding& operator=(VideoDecoding&&) = delete;

    virtual ~VideoDecoding() = default;

public:
    /**
     * @brief 获取输入源的下一帧
     * @param frame_tensor
     * @return
     */
    virtual int next(FrameTensor &frame_tensor) = 0;

    /**
     * @brief 显示当前frame_tensor中的视频帧
     * @param frame_tensor
     * @return
     */
    virtual int display(const FrameTensor &frame_tensor) = 0;

    /**
     * @brief 将当前frame_tensor中的视频帧写为本地视频文件
     * @param frame_tensor
     * @return
     */
    virtual int save(FrameTensor &frame_tensor) = 0;

    /**
     * @brief 获取视频的fps属性
     * @return
     */
    virtual int get_fps() = 0;
     /**
      * @brief 获取视频的width属性
      * @return
      */
    virtual int get_width() = 0;

    /**
     * @brief 获取视频的height属性
     * @return
     */
    virtual int get_height() = 0;
};

} // namespace easyedge