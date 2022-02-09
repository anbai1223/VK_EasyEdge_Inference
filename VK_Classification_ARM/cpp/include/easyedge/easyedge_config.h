/***************************************************************************
 * 
 * Copyright (c) 2020 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/

/**
 * @author Baidu
 * @date 2020/5/19
 * @brief controller 和 predictor的配置项
 *
 * 其中CONTROLLER_KEY_XXX，用于全局的一些配置，使用方法如下：
 * @code global_controller()->set_config(easyedge::params::CONTROLLER_KEY_XXX, value) @endcode
 *
 *
 * 其中PREDICTOR_KEY_XXX，用于每个predictor的配置，使用方法如下：
 * @code predictor->set_config(easyedge::params::PREDICTOR_KEY_XXXX, value) @endcode
 *
 * value 的类型参考各配置的说明。
 *
 * 除非特殊说明，所有的配置项均可通过环境变量来设置
 * （对应的环境变量加上"EDGE_"前缀，如CONTROLLER_KEY_LOG_BRAND的环境变量为EDGE_CONTROLLER_KEY_LOG_BRAND)
 * 请注意，通过代码set_config设置的配置项，将会覆盖环境变量的设置的配置项
 *
 **/

#pragma once

namespace easyedge {

namespace params {

/// ----------------- 以下为controller的配置项 --------------------   ////


/**
 * @brief 配置品牌名称，该名称会显示在日志和HTTP Serving的标题中
 * 值类型：string
 * 默认值：EasyEdge
 */
static constexpr auto CONTROLLER_KEY_LOG_BRAND = "CONTROLLER_KEY_LOG_BRAND";

/**
 * @brief 配置是否打开 debug 日志；也可以通过 @code global_controller()->set_log_config @endcode 配置
 * 值类型：bool
 * 默认值：false
 */
static constexpr auto CONTROLLER_KEY_ENABLE_DEBUG_LOG = "CONTROLLER_KEY_ENABLE_DEBUG_LOG";

/**
 * @brief 配置是否打开 info 日志；也可以通过 @code global_controller()->set_log_config @endcode 配置
 * 值类型：bool
 * 默认值：false
 */

static constexpr auto CONTROLLER_KEY_ENABLE_INFO_LOG = "CONTROLLER_KEY_ENABLE_INFO_LOG";

/**
 * @brief 配置是否打开 warning 日志；也可以通过 @code global_controller()->set_log_config @endcode 配置
 * 值类型：bool
 * 默认值：false
 */

static constexpr auto CONTROLLER_KEY_ENABLE_WARNING_LOG = "CONTROLLER_KEY_ENABLE_WARNING_LOG";

/**
 * @brief http serving中创建的predictor的实例数
 * 值类型: int
 * 默认值：1
 */
static constexpr auto CONTROLLER_KEY_SERVING_INSTANCE_NUM = "CONTROLLER_KEY_SERVING_INSTANCE_NUM";

/**
 * @brief 设置鉴权模式
 * 值类型: int
 * 默认值：1
 * 1: 默认鉴权模式   2: 实例数鉴权模式
 */
static constexpr auto CONTROLLER_KEY_AUTH_MODE = "CONTROLLER_KEY_AUTH_MODE";

/**
 * @brief 实例数鉴权场景下设置更新本地license间隔时间
 * 值类型: int
 * 默认值：3600
 * 单位：秒
 */
static constexpr auto CONTROLLER_KEY_INSTANCE_UPDATE_INTERVAL = "CONTROLLER_KEY_INSTANCE_UPDATE_INTERVAL";

/// -------------------- 以下为predictor的配置项 --------------------   ////
/**
 * @brief 序列号设置；序列号不设置留空时，SDK将会自动尝试使用本地已经激活成功的有效期内的序列号
 * 值类型：string
 * 默认值：空
 */
static constexpr auto PREDICTOR_KEY_SERIAL_NUM = "PREDICTOR_KEY_SERIAL_NUM";

/**
 * @brief 当有同类型的多个设备的时候，使用哪一个设备，如：
 * GPU: 使用哪张GPU卡
 * EdgeBoard(VMX)，Movidius NCS ：使用哪一张加速卡
 * 值类型：int
 * 默认值：0
 */
static constexpr auto PREDICTOR_KEY_DEVICE_ID = "PREDICTOR_KEY_DEVICE_ID";

/**
 * @brief 指定使用的CPU线程数。 一般来说，线程数越接近物理核数，速度越快。
 * 该参数表示在一次识别过程中，同时使用多少CPU线程。
 * 若期望同时使用多个线程来同时识别多张图片，可自行创建多个predictor来使用。
 * 值类型: int
 * 默认值：4
 */
static constexpr auto PREDICTOR_KEY_CPU_THREADS_NUM = "PREDICTOR_KEY_CPU_THREADS_NUM";

}

}
