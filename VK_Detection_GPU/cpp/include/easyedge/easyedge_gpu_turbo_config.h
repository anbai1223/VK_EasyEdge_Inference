/***************************************************************************
 *
 * Copyright (c) 2020 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

/**
 * @author Baidu
 * @date 2020/12/8
 * @brief
 *
 **/

#pragma once

namespace easyedge {

namespace params {

/**
 * @brief 生成最大 batch_size 为 max_batch_size 的优化模型，单次预测图片数量可以小于或等于此值
 * 值类型: int
 * 默认值：4
 */
static constexpr auto PREDICTOR_KEY_GTURBO_MAX_BATCH_SIZE = "PREDICTOR_KEY_GTURBO_MAX_BATCH_SIZE";

/**
 * @brief int8量化使用的batch个数
 * 值类型: int
 * 默认值：4
 */
static constexpr auto PREDICTOR_KEY_GTURBO_INT8_CALIBRATOR_BATCHES = "PREDICTOR_KEY_GTURBO_INT8_CALIBRATOR_BATCHES";

/**
 * @brief int8量化使用的每个batch的大小
 * 值类型: int
 * 默认值：4
 */
static constexpr auto PREDICTOR_KEY_GTURBO_INT8_CALIBRATOR_BATCH_SIZE = "PREDICTOR_KEY_GTURBO_INT8_CALIBRATOR_BATCH_SIZE";

/**
 * @brief int8量化使用的训练图像的位置
 * 值类型: string
 * 默认值：./
 */
static constexpr auto PREDICTOR_KEY_GTURBO_INT8_CALIBRATOR_TRAIN_SET_DIR = "PREDICTOR_KEY_GTURBO_INT8_CALIBRATOR_TRAIN_SET_DIR";

/**
 * @brief int8量化推理的校准表文件名
 * 值类型: string
 * 默认值：./
 */
static constexpr auto PREDICTOR_KEY_GTURBO_INT8_CALIBRATOR_TABLE_NAME = "PREDICTOR_KEY_GTURBO_INT8_CALIBRATOR_TABLE_NAME";

/**
 * @brief 设置device对应的GPU卡可以支持的最大并发量
 * 实际预测的时候对应GPU卡的最大并发量不超过这里设置的范围，否则预测请求会排队等待预测执行
 * 值类型: int
 * 默认值：1
 */
static constexpr auto PREDICTOR_KEY_GTURBO_MAX_CONCURRENCY = "PREDICTOR_KEY_GTURBO_MAX_CONCURRENCY";

/**
 * @brief 是否开启fp16模式预测，开启后预测速度会更快，但精度会略有降低。并且需要硬件支持fp16计算
 * 值类型: bool
 * 默认值：false
 */
static constexpr auto PREDICTOR_KEY_GTURBO_FP16 = "PREDICTOR_KEY_GTURBO_FP16";

/**
 * @brief 是否开启int8模式预测，开启后预测速度会更快，但精度会略有降低。需要满足如下条件：
 *     1. 硬件支持int8计算
 *     2. 模型路径存在校准文件，文件名可通过PREDICTOR_KEY_GTURBO_INT8_CALIBRATOR_TABLE_NAME设定
 * 值类型: bool
 * 默认值：false
 */
static constexpr auto PREDICTOR_KEY_GTURBO_INT8 = "PREDICTOR_KEY_GTURBO_INT8";

/**
 * @brief 模型编译等级
 * 0：无论当前设置的max_batch_size是多少，仅使用历史编译产出（如果存在）
 * 1：如果当前max_batch_size与历史编译产出的max_batch_size不相等时，则重新编译模型（推荐）
 * 2：无论历史编译产出的max_batch_size为多少，均根据当前max_batch_size重新编译模型
 * 值类型: int
 * 默认值：1
 */
static constexpr auto PREDICTOR_KEY_GTURBO_COMPILE_LEVEL = "PREDICTOR_KEY_GTURBO_COMPILE_LEVEL";

/**
 * @brief GPU工作空间大小设置
 * workspace_size = workspace_prefix * (1 << workspace_offset)
 * workspace_offset: 10 = KB, 20 = MB, 30 = GB
 * 值类型: int
 * 默认值：WORKSPACE_PREFIX: 100, WORKSPACE_OFFSET: 20
 */
static constexpr auto PREDICTOR_KEY_GTURBO_WORKSPACE_PREFIX = "PREDICTOR_KEY_GTURBO_WORKSPACE_PREFIX";
static constexpr auto PREDICTOR_KEY_GTURBO_WORKSPACE_OFFSET = "PREDICTOR_KEY_GTURBO_WORKSPACE_OFFSET";

/**
 * @brief 需要使用的dla core
 * 值类型: int
 * 默认值：-1(不使用)
 */
static constexpr auto PREDICTOR_KEY_GTURBO_DLA_CORE = "PREDICTOR_KEY_GTURBO_DLA_CORE";

/**
 * @brief 自定义缓存文件存储路径
 * 值类型: string
 * 默认值: ~/.baidu/easyedge/mcache/{model_id * 1000000 + release_id}
 */
static constexpr auto PREDICTOR_KEY_GTURBO_CACHE_DIR = "PREDICTOR_KEY_GTURBO_CACHE_DIR";

/**
 * @brief 自定义缓存文件命名，默认即可
 * 值类型: string
 * 默认值: 根据config配置自动生成
 */
static constexpr auto PREDICTOR_KEY_GTURBO_CACHE_NAME = "PREDICTOR_KEY_GTURBO_CACHE_NAME";

} // namespace params
} // namespace easyedge

