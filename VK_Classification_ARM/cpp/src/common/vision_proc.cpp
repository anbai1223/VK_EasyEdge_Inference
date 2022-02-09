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

#include "vision_proc.h"

#if defined(WIN32) || defined(_WIN32)

#ifndef S_ISREG
#define S_ISREG(m) (((m)&S_IFREG) == S_IFREG)
#endif // S_ISREG

#ifndef S_ISDIR
#define S_ISDIR(m) (((m)&S_IFDIR) == S_IFDIR)
#endif // S_ISDIR

#endif

namespace easyedge {

bool is_file(const std::string &path) {
    struct stat st;
    return stat(path.c_str(), &st) >= 0 && S_ISREG(st.st_mode);
}

bool list_files(std::string &folder_path, std::vector<std::string> &files, const std::string &ext) {
    try {
        if (is_file(folder_path)) {
            files.push_back(folder_path);
            return true;
        }
        for (auto &f : fs::directory_iterator(folder_path)) {
            files.push_back(f.path().generic_string());
        }
    }
    catch (fs::filesystem_error &) {
        // 目录不存在
        return false;
    }
    return true;
}

bool get_next_batch(std::vector<cv::Mat>& images,
                    const std::vector<std::string>& files,
                    const int batch_size,
                    const int start_index) {
    const int num_images = files.size();
    int end_index = start_index + batch_size > num_images ? num_images : start_index + batch_size;
    for (int i = start_index; i < end_index; ++i) {
        // 如果图像旋转有问题，请注意图像的exif信息，如果需要丢弃exif信息，请设置
        // images.push_back(cv::imread(files[i], cv::IMREAD_COLOR | cv::IMREAD_IGNORE_ORIENTATION));
        images.push_back(cv::imread(files[i]));
    }
    return start_index < end_index;
}

void render(cv::Mat &frame,
        const std::vector<EdgeResultData> &result,
        const EdgeModelKind &model_kind,
        const std::string &save_frame_path) {
    if (result.empty()) {
        std::cout << "empty result" << std::endl;
        return;
    }
    switch (model_kind) {
    case EdgeModelKind::kImageClassification: {
        for (int i = 0; i < result.size(); ++i) {
            std::cout << result[i].index << ", " << result[i].label << ", p:" << result[i].prob << std::endl;
            int x = 20;
            int y = 40 + 20 * i;
            if (y > frame.rows) {
                continue;
            }
            auto p1 = cv::Point(x, y);
            cv::putText(frame, result[i].label + " " + std::to_string(result[i].prob), p1, cv::FONT_HERSHEY_PLAIN, 1.2,
                        RED, 1);
        }
        break;
    }
    case EdgeModelKind::kObjectDetection:
    case EdgeModelKind::kFaceDetection: {
        for (auto &v : result) {
            std::cout << v.index << ", " << v.label << ", p:" << v.prob
                      << ", coordinate: " << v.x1 << ", " << v.y1 << ", " << v.x2 << ", " << v.y2 << std::endl;
            auto p1 = cv::Point(static_cast<int>(v.x1 * static_cast<float>(frame.cols)),
                                static_cast<int>(v.y1 * static_cast<float>(frame.rows)));
            auto p2 = cv::Point(static_cast<int>(v.x2 * static_cast<float>(frame.cols)),
                                static_cast<int>(v.y2 * static_cast<float>(frame.rows)));
            cv::rectangle(frame, p1, p2, RED, 2);
            cv::putText(frame, v.label + " " + std::to_string(v.prob), p1, cv::FONT_HERSHEY_PLAIN, 1.2,
                        RED, 1);
        }
        break;
    }
    case EdgeModelKind::kImageSegmentation: {
        for (auto &v : result) {
            std::cout << v.index << ", " << v.label << ", p:" << v.prob << std::endl;
            auto p1 = cv::Point(static_cast<int>(v.x1 * static_cast<float>(frame.cols)),
                                static_cast<int>(v.y1 * static_cast<float>(frame.rows)));
            auto p2 = cv::Point(static_cast<int>(v.x2 * static_cast<float>(frame.cols)),
                                static_cast<int>(v.y2 * static_cast<float>(frame.rows)));
            cv::rectangle(frame, p1, p2, RED, 2);
            cv::putText(frame, v.label + " " + std::to_string(v.prob), p1, cv::FONT_HERSHEY_PLAIN, 1.2,
                        RED, 1);
            cv::Mat tmp(frame.rows, frame.cols, CV_8UC3, cv::Scalar(0, 0, 0));
            cv::Vec3b random_color((v.index + 3) * 13 % 255,
                                   (v.index + 7) * 19 % 255,
                                   (v.index + 11) * 29 % 255);
            for (int y = 0; y < tmp.rows; ++y) {
                for (int x = 0; x < tmp.cols; ++x) {
                    if (v.mask.at<uint8_t>(y, x) == 1) {
                        tmp.at<cv::Vec3b>(y, x) = random_color;
                    }
                }
            }
            // 图片融合
            cv::addWeighted(tmp, 0.95, frame, 1, 0.0, frame);
        }
        break;
    }
    case EdgeModelKind::kSemanticSegmentation: {
        if (result.size() != 1) {
            std::cout << "Semantic segmentation: check result size failed." << std::endl;
            exit(-1);
        }
        cv::Mat semantic = result[0].mask;
        cv::Mat colored_img(semantic.rows, semantic.cols, CV_8UC3);

        std::vector<cv::Vec3b> color_map_backup;
        int color_map_size = 19; // index: 0~19

        for(auto x = 0; x < colored_img.rows; ++x) {
            for(auto y = 0; y < colored_img.cols; ++y) {
                uint8_t label = semantic.at<uint8_t>(x,y);
                if (label > 255) {
                    std::cout << "Label size could not be larger than 255." << std::endl;
                    exit(-1);
                }

                if (label > color_map_size) {
                    auto tmp_nums = label - color_map_size;
                    for (auto k = 0; k < tmp_nums; ++k) {
                        auto index = color_map_size + k;
                        cv::Vec3b random_color((index + 3) * 13 % 255,
                                               (index + 7) * 19 % 255,
                                               (index + 11) * 29 % 255);
                        color_map_backup.emplace_back(random_color);
                    }
                    color_map_size = label;
                }

                if (label < 20) {
                    colored_img.at<cv::Vec3b>(x,y) = color_map_default[label];
                } else {
                    colored_img.at<cv::Vec3b>(x,y) = color_map_backup[label - 20];
                }
            }
        }
        // 图片融合
        cv::addWeighted(colored_img, 0.95, frame, 1, 0.0, frame);
        break;
    }
    case EdgeModelKind::kPoseEstimation: {
        for (auto &v : result) {
            std::cout << v.index << ", " << v.label << ", p:" << v.prob
                      << ", coordinate: " << v.x1 << ", " << v.y1 << std::endl;
            auto p1 = cv::Point(static_cast<int>(v.x1 * static_cast<float>(frame.cols)),
                                static_cast<int>(v.y1 * static_cast<float>(frame.rows)));
            cv::circle(frame, p1, 4, BLUE, -1, 8);
            for (int pair_id : v.point_pairs) {
                EdgeResultData pairData = result[pair_id];
                auto p2 = cv::Point(static_cast<int>(pairData.x1 * static_cast<float>(frame.cols)),
                                    static_cast<int>(pairData.y1 * static_cast<float>(frame.rows)));
                cv::line(frame, p1, p2, RED, 4);
            }
        }
        break;
    }
    case EdgeModelKind::kObjectTracking: {
        std::vector<cv::Scalar> colors{BLUE, GREEN, RED, PINK, BLACK};
        for (auto &v : result) {
            if (v.track_stat != EdgeTrackStat::kTrackStatTracked) {
                std::cout << "track lost: " << v.trackid << std::endl;
                continue;
            }
            auto track_color = colors[v.trackid % colors.size()];
            auto p1 = cv::Point(static_cast<int>(v.x1 * static_cast<float>(frame.cols)),
                                static_cast<int>(v.y1 * static_cast<float>(frame.rows)));
            auto p2 = cv::Point(static_cast<int>(v.x2 * static_cast<float>(frame.cols)),
                                static_cast<int>(v.y2 * static_cast<float>(frame.rows)));
            cv::rectangle(frame, p1, p2, track_color, 2);
            std::stringstream txt;
            txt << "ID:" << v.trackid;
            cv::putText(
                frame, txt.str(), p1,
                cv::FONT_HERSHEY_PLAIN, 1.2, track_color, 1);
        }
        break;
    }
    default: {
        std::cout << "Not implemented render for model kind: " << static_cast<int>(model_kind) << std::endl;
    }
    }

    if (!save_frame_path.empty()) {
        std::cout << "save result image to " << save_frame_path << std::endl;
        cv::imwrite(save_frame_path, frame);
    }
}

}