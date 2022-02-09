/***************************************************************************
 *
 * Copyright (c) 2021 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @author Baidu
 * @brief frame buffer
 *
 **/
#include "frame_buffer.h"

namespace easyedge {

void FrameBuffer::put_frame(FrameTensor &frame) {
    _mu_frame.lock();
    if(_frame_buffer.size() > _buffer_size) {
        std::vector<FrameTensor>::iterator k = _frame_buffer.begin();
        _frame_buffer.erase(k);
    }
    _frame_buffer.emplace_back(frame);
    _mu_frame.unlock();
}

int FrameBuffer::change_frame(FrameTensor &frame) {
    _mu_frame.lock();
    for(int i = 0; i < _frame_buffer.size(); i++) {
        if(_frame_buffer[i].frame_id == frame.frame_id) {
            _frame_buffer[i] = frame;
            _mu_frame.unlock();
            return 0;
        }
    }
    _frame_buffer.front() = frame;
    std::cout << "the infer time is too long, the infer size is not enough!" << std::endl;
    _mu_frame.unlock();
    return 1;
}

int FrameBuffer::change_frame(FrameTensor &frame, 
                              const std::vector<EdgeResultData> &results, 
                              const EdgeModelKind &model_kind) {
    _edge_model_kind = model_kind;
    _mu_frame.lock();
    for(int i = 0; i < _frame_buffer.size(); i++) {
        if(_frame_buffer[i].frame_id == frame.frame_id) {
            _frame_buffer[i] = frame;
            _mu_frame.unlock();
            for(int i = 0; i < _render_size; i++) {
                _render_map.insert(std::make_pair(frame.frame_id+i+1, results));
                std::cout << "add result to " << frame.frame_id+i+1 << std::endl;
            }
            return 0;
        }
    }
    _frame_buffer.front().frame = frame.frame; 
    std::cout << "the infer time is too long, the infer size is not enough!" << std::endl;
    _mu_frame.unlock();
    for(int i = 0; i < _render_size; i++) {
        _render_map.insert(std::make_pair(frame.frame_id+i+1, results));
        std::cout << "add result to " << frame.frame_id+i+1 << std::endl;
    }   
    return 1;
}

bool FrameBuffer::get_frame(FrameTensor &frame)
{
    _mu_frame.lock();
    if(_frame_buffer.size() < 1) {
        _mu_frame.unlock();
        return false;
    }
    else {
        frame = _frame_buffer.front();
        std::vector<FrameTensor>::iterator k = _frame_buffer.begin();
        _frame_buffer.erase(k);
    }
    _mu_frame.unlock();
    auto n = _render_map.count(frame.frame_id);
    if (n >= 1) {
        auto range = _render_map.equal_range(frame.frame_id);
        while(range.first != range.second)
        {
            render(frame.frame, range.first->second, _edge_model_kind);
            std::cout << "render " << frame.frame_id << std::endl;
            ++range.first;
        }
        _render_map.erase(_render_map.find(frame.frame_id), _render_map.end());
    }
    return true;
}

bool FrameBuffer::get_frame_clone(FrameTensor &frame)
{
    _mu_frame.lock();
    if(_frame_buffer.size() < 1) {
        _mu_frame.unlock();
        return false;
    }
    else {
        frame = _frame_buffer.back();
    }
    _mu_frame.unlock();
    return true;
}

int FrameBuffer::get_size()
{
    _mu_frame.lock();
    int size = _frame_buffer.size();
    _mu_frame.unlock();
    return size;
}

int FrameBuffer::get_infer_size()
{
    return _infer_size;
}

bool FrameBuffer::allow_encode()
{
    _mu_frame.lock();
    int size = _frame_buffer.size();
    _mu_frame.unlock();
    return _infer_size < size;
}

}