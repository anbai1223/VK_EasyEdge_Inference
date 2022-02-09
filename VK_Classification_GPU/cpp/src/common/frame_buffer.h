/***************************************************************************
 *
 * Copyright (c) 2021 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @author Baidu
 * @brief frame buffer
 *
 * change_frame:将infer之后的frame替换frame buffer中对应的帧, 这个是在整个frame buffer里做
 * encode:只能编码frame buffer中位置大于infer size的帧 
 *  
 * ----------------------------------------------------------------------------------------
 *   |infer buffer                 |   encode buffer  |                 |
 * ----------------------------------------------------------------------------------------
 *   ^                                                ^                 ^                  ^
 *   |                                                |                 |                  |
 * get_frame_clone(拷贝一帧进行infer)               infer size         get_frame        buffer size
 * 
 **/
#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <unordered_map>
#include "easyedge.h"
#include "easyedge_video.h"
#include "vision_proc.h"

namespace easyedge {

class FrameBuffer {
public:
    FrameBuffer() {};
    FrameBuffer(int buffer_size, int infer_size = 1, int render_size = 0) : 
    _buffer_size(buffer_size), _infer_size(infer_size), _render_size(render_size) {
        if(buffer_size < 0) {
            _buffer_size = 10;
            std::cout << "buffer size must > 0, now buffer size is the default size 10" << std::endl;
        }
        if(infer_size < 0) {
            _infer_size = 1;
            std::cout << "infer size must > 0, now infer size is the default size 1" << std::endl;
        }
        if(render_size <= 0) {
            _render_size = 0;
            std::cout << "render size must >= 0, now render size is the default size 0" << std::endl;
        }
        std::cout << "buffer size: " << _buffer_size 
                  << ", infer size: " << _infer_size 
                  << ", render size: " << _render_size 
                  << std::endl;
    };
    ~FrameBuffer() = default;

    /**
     * @brief 将frame放入frame buffer中
     * @param frame
     */
    void put_frame(FrameTensor &frame);

    /**
     * @brief 将infer之后的frame替换frame buffer中对应的帧
     * @param frame
     */    
    int change_frame(FrameTensor &frame);

    /**
     * @brief 将infer之后的frame替换frame buffer中对应的帧，保留渲染效果至下几帧
     * @param frame
     * @param results
     * @param model_kind
     */ 
    int change_frame(FrameTensor &frame, 
                     const std::vector<EdgeResultData> &results, 
                     const EdgeModelKind &model_kind);
    
    /**
     * @brief 从frame buffer中获取最旧的一帧，如若之前有记录该帧有保留渲染效果，增加渲染效果
     * @param frame
     */     
    bool get_frame(FrameTensor &frame);

    /**
     * @brief 从frame buffer中拷贝最新的一帧
     * @param frame
     */     
    bool get_frame_clone(FrameTensor &frame);

    /**
     * @brief 获取frame buffer的大小
     */  
    int get_size();

    /**
     * @brief 获取frame buffer中供查找infer对应帧缓冲区的大小
     */  
    int get_infer_size();

    /**
     * @brief 判断该frame buffer目前frame的数量是否允许编码
     */  
    bool allow_encode();

private:
    std::vector<FrameTensor> _frame_buffer;
    std::mutex _mu_frame;
    int _buffer_size = 10; // frame buffer的大小
    int _infer_size = 1; // 供查找infer对应帧缓冲区的大小
    int _render_size = 0; // 每次渲染效果多保留的帧数
    std::unordered_multimap<int, std::vector<EdgeResultData>> _render_map; // 记录每一帧所保留的渲染效果
    EdgeModelKind _edge_model_kind; 
};

}