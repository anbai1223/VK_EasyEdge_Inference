/***************************************************************************
 *
 * Copyright (c) 2021 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @author Baidu
 * @brief vision process
 *
 **/
#pragma once

#include <chrono>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <memory>
#include <vector>

#include "easyedge.h"
#include "easyedge_video.h"

#if __cplusplus == 201402L
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif __cplusplus >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#elif defined(WIN32) || defined(_WIN32)
#if _MSVC_LANG == 201402L
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif _MSVC_LANG >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#endif
#endif

namespace easyedge {

const cv::Vec3b color_map_default[] = {
    cv::Vec3b(128, 64, 128),
    cv::Vec3b(244, 35, 232),
    cv::Vec3b(70, 70, 70),
    cv::Vec3b(102, 102, 156),
    cv::Vec3b(190, 153, 153),
    cv::Vec3b(153, 153, 153),
    cv::Vec3b(250, 170, 30),
    cv::Vec3b(220, 220, 0),
    cv::Vec3b(107, 142, 35),
    cv::Vec3b(152, 251, 152),
    cv::Vec3b(70, 130, 180),
    cv::Vec3b(220, 20, 60),
    cv::Vec3b(255, 0, 0),
    cv::Vec3b(0, 0, 142),
    cv::Vec3b(0, 0, 70),
    cv::Vec3b(0, 60, 100),
    cv::Vec3b(0, 80, 100),
    cv::Vec3b(0, 0, 230),
    cv::Vec3b(119, 11, 32),
    cv::Vec3b(0, 0, 0)
};

/**
 * @brief 判断path所指向路径是否为普通文件
 * @param path
 * @return
 */
bool is_file(const std::string &path);

/**
 * @brief 遍历指定目录中的文件，单级目录搜索
 * @param path 要遍历的目录或文件
 * @param files 搜索得到的文件
 * @return true for success
 */
bool list_files(std::string &folder_path, std::vector<std::string> &files, const std::string &ext = "");

/**
 * @brief 从files中获取batch_size个image，并imread进images
 * @param images
 * @param files
 * @param batch_size
 * @param start_index
 * @return
 */
bool get_next_batch(std::vector<cv::Mat> &images,
        const std::vector<std::string> &files,
        int batch_size,
        int start_index);

/**
 * @brief 图片渲染函数，将识别结果覆盖在图片或视频frame中
 * @param frame
 * @param result
 * @param model_kind
 */
void render(cv::Mat &frame,
        const std::vector<EdgeResultData> &result,
        const EdgeModelKind &model_kind,
        const std::string &save_frame_path = "");

} // namespace easyedge
