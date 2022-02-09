#ifndef BAIDU_EASYEDGE_LIBRARY_H
#define BAIDU_EASYEDGE_LIBRARY_H

#include <string>
#include <memory>
#include <map>

// opencv3
#include "opencv2/opencv.hpp"

#include "easyedge_config.h"

#ifndef EASYEDGE_PUBLIC_API
#define EASYEDGE_PUBLIC_API
#endif

namespace easyedge {

#define EDGE_CONFIG_DEPRECATED [[deprecated("Since 1.0, use EdgePredictorConfig instead")]]

const cv::Scalar BLUE = cv::Scalar(255, 0, 0, 255);
const cv::Scalar GREEN = cv::Scalar(0, 255, 0, 255);
const cv::Scalar RED = cv::Scalar(0, 0, 255, 255);
const cv::Scalar PINK = cv::Scalar(255, 80, 180, 255);
const cv::Scalar BLACK = cv::Scalar(0, 0, 0, 255);

enum EdgeStatus {
    EDGE_OK = 0,
    EDGE_FAILED = 1,

    EDGE_INNER_FAILED = 1000000,
    EDGE_DEVICE_NOT_FOUND = 1000001,
    EDGE_DEVICE_OPEN_FAIL = 1000002,

    EDGE_MODEL_LOAD_FAIL = 1000003,
    EDGE_RESOURCE_LOAD_FAIL = 1000004, // 模型资源文件目录不存在或者文件有缺失
    EDGE_MODEL_DEC_FAIL = 1000005,  // 资源文件有误
    EDGE_IMAGE_LOAD_FAIL = 1000006,
    EDGE_NOT_SUPPORTED_MODEL = 1000007,  // 暂不支持该模型
    EDGE_KIT_VERSION_INCOMPATIBLE = 1000008,  // SDK 版本过旧，请使用最新的SDK
    EDGE_ENV_CHECK_FAIL = 1000009, // 环境不符合要求
    EDGE_EOF = 1000010, // 到达文件结尾
    EDGE_PARAMS_INVALID = 1000011,

    EDGE_INFER_FAIL = 2000001,
    EDGE_INFER_NCS_FAIL = 2000002,

    EDGE_NET_CURL_PERFORM_FAILED = 500001,
    EDGE_GET_MACHINE_ID_FAILED = 600001,

    // 错误码在日志中打印，edge-desktop会使用到，不要改
    EDGE_AUTH_FAILED = 7000001,
    EDGE_AUTH_LICENSE_INVALID = 7000002,  // 序列号无效
    EDGE_AUTH_LICENSE_EXPIRED = 7000003,  // 序列号过期
    EDGE_AUTH_TIME_MISMATCH = 7000004,    // 本地时间不正确
    EDGE_AUTH_SK_CHECK_FAILED = 7000005,  // 实例数鉴权场景sk校验失败

    EDGE_SERVING_ILLEGA_INPUT = 8000001,
    EDGE_SERVING_START_FAIL = 8000002,
    EDGE_SERVING_INVALID_PARAM = 8000003,

    /// @deprecated XEYE 不再支持
    EDGE_XEYE_CREATE_INSTANCE_FAIL = 9000001,  // 计算模式下，请稍等再试；标准模式下，请重新拔插设备
    EDGE_XEYE_START_FAIL = 9000002,
    EDGE_XEYE_NOT_RESPONDING = 9000003,  // 计算模式下，请稍等再试；标准模式下，请重新拔插设备

    EDGE_GPU_TURBO_INNER_FAIL = 1100001,
    EDGE_GPU_TURBO_CONFIG_FAIL = 1100002,
    EDGE_GPU_TURBO_RESOURCE_FAIL = 1100003,
    EDGE_GPU_TURBO_MODEL_COMPILE_FAIL = 1100004,
    EDGE_GPU_TURBO_OP_COMPUTE_FAIL = 1100005,
    EDGE_GPU_TURBO_CALIBRATIONTABLE_LOAD_FAIL = 1100006,// 没有找到或无法生成int8校准表
    EDGE_GPU_TURBO_INFERENCE_PRECISION_NOT_SUPPORTED = 1100007, // 不支持的计算精度

    EDGE_ATLAS_UNKONWN = 12000001,
    EDGE_ATLAS_INTERNAL = 12000002,
    EDGE_ATLAS_MEMORY = 12000003,
    EDGE_ATLAS_FILE_NOT_READABLE = 12000011,
    EDGE_ATLAS_HIAI_ERRORLIST_FILE = 1200012,
    EDGE_ATLAS_PREDICTOR_NOT_INITED = 12000102,
    EDGE_ATLAS_PREDICTOR_NO_HANDLER = 12000103,
    EDGE_ATLAS_PREDICTOR_ALREADY_INITED = 12000104,
    EDGE_ATLAS_BATCH_SIZE = 12000105,
    EDGE_ATLAS_INPUT_WIDTH = 12000106,
    EDGE_ATLAS_INPUT_HEIGHT = 12000107,
    EDGE_ATLAS_BATCH_TOO_MANY_IMAGES = 12000201,
    EDGE_ATLAS_IMAGE_FORMAT_CHANNELS = 12000202,
    EDGE_ATLAS_ENGINE_COMMON = 12200000,
    EDGE_ATLAS_ENGINE_MATRIX_COMMON = 12200001,
    EDGE_ATLAS_ENGINE_AI_COMMON = 12200002,
    EDGE_ATLAS_ENGINE_MATRIX_INIT = 12200003,
    EDGE_ATLAS_ENGINE_MATRIX_INIT_DEVICE = 12200004,
    EDGE_ATLAS_ENGINE_ARGS_NULL = 12200005,
    EDGE_ATLAS_SYNC_INFER_TIMEOUT = 12300001,

    EDGE_MYRIAD_NO_AVAILABLE_DEVICE = 13000001,  // 找不到可用的设备
    EDGE_MYRIAD_DEVICE_NOT_FOUND = 13000002,  // 找不到指定的设备id

    EDGE_CANN_INTERAL = 14000000,
    EDGE_CANN_UNKONWN = 14000001,
    EDGE_CANN_FORWARD_INPUT_TOO_MANY = 14000002,
    EDGE_CANN_FORWARD_INPUT_SIZE = 14000003,
    EDGE_CANN_FACE_DETECT_STRUCT_JSON_MISSING = 14000004,
    EDGE_CANN_FACE_DETECT_STRUCT_JSON_FORMAT = 14000005,
    EDGE_CANN_FACE_DETECT_STRUCT_FILL_SSD = 14000006,
    EDGE_CANN_CONTROLLER_NOT_INITED = 14000007,
    EDGE_CANN_PROTO_STRUCT_MISSING = 14000008,
    EDGE_CANN_IMAGE_SIZE_ZERO = 14000009,
    EDGE_CANN_PREPROCESS_SIZE_NOT_EQUAL = 14000010,
    EDGE_CANN_RESULT_TENSORS_EMPTY = 14000011,
    EDGE_CANN_RESULT_BATCH_SIZE_NOT_CORRECT = 14000012,
    EDGE_CANN_MODEL_FILE_NOT_EXIST = 14000013,
    EDGE_CANN_RESULT_TENSORS_BATCH_NOT_MATCH = 14000014,
    EDGE_CANN_ACL_ERROR = 14100000,
};

enum class EdgeEngineKind {
    kNativePaddleV2 = 0,
    kNativeTensorflow = 1,
    kNCS = 2,
    kPaddleMobile = 3,
    kPaddleFluid = 4,
    kTensorRT = 5,
    kNNIE = 6,
    kXTCL = 7
};

enum EdgeModelKind {
    kImageClassification = 1,
    kObjectDetection = 2,
    kSoundClassification = 3,
    kImageSegmentation = 6,
    kObjectTracking = 12,
    kSemanticSegmentation = 14,
    kFaceDetection = 401,
    kPoseEstimation = 402,
    kOCR = 100,
    kDecision = 10001,
};

enum EdgeRescaleMode {
    kKeepSize = 0,
    kKeepRatio = 1,
    kKeepRatio2 = 2,
    kKeepRawSize = 3,
};

enum EdgeColorFormat {
    kUnknown = 0,
    kRGB = 1,
    kBGR = 2,
    kYUV = 5,
    kGRAY = 6,
    kRGBA = 101,
    kBGRA = 102,

};

enum EdgeChannelOrd {
    kUnknownOrd = 0,
    kCHW = 1,
    kHWC = 2,
};

struct EASYEDGE_PUBLIC_API EdgeLogConfig {
    bool enable_debug = false;
    bool enable_info = true;
    bool enable_warning = true;
    bool to_file = false; // 输出到文件
    bool to_std = true;  // 输出到 标准输出
    bool to_std_colorful = false;  // 输出至std时带彩色
    uint32_t max_log_file_size = 102400;
    std::string log_file_path{"easyedge.log"};
};

struct EASYEDGE_PUBLIC_API EdgePredictorConfig {
    /**
     * @brief 模型资源文件夹路径
     */
    std::string model_dir;

    std::map<std::string, std::string> conf;

    EdgePredictorConfig();

    template<typename T>
    T get_config(const std::string &key, const T &default_value);

    template<typename T = std::string>
    T get_config(const std::string &key);

    template<typename T>
    const T *get_config(const std::string &key, const T *default_value);

    template<typename T>
    void set_config(const std::string &key, const T &value);

    template<typename T>
    void set_config(const std::string &key, const T *value);

    static EdgePredictorConfig default_config();
};

struct EDGE_CONFIG_DEPRECATED EASYEDGE_PUBLIC_API PaddleV2Config : public EdgePredictorConfig {
    std::string model_filename{"capi_model.paddle"};  // 模型文件名
};

struct EDGE_CONFIG_DEPRECATED EASYEDGE_PUBLIC_API PaddleFluidConfig : public EdgePredictorConfig {
    std::string model_filename{"model"};
    std::string params_filename{"params"};

    int thread_num = 4;

    // ----- GPU related -----
    bool use_gpu{false};
    /**
     * @brief 使用哪张GPU卡
     */
    int device{0};

    /**
     * @brief 该参数标识 SDK初始会使用多少比例的gpu内存（0~1）
     */
    float fraction_of_gpu_memory{0.01f};
    // ----- end of GPU related ----
};

struct EDGE_CONFIG_DEPRECATED EASYEDGE_PUBLIC_API PaddleMultiStageConfig : public PaddleFluidConfig {
    std::vector<std::string> submodel_tags;
};

struct EDGE_CONFIG_DEPRECATED EASYEDGE_PUBLIC_API NCSConfig : public EdgePredictorConfig {
    int device{0};  // which NCS to use

    std::string graph_filename{"graph.ncsmodel"};
};

// struct EDGE_CONFIG_DEPRECATED EASYEDGE_PUBLIC_API CambriconConfig : public EdgePredictorConfig {

//     // std::string label_path = "label_list.txt";

//     int max_batch_size = 1;
// };

struct EDGE_CONFIG_DEPRECATED EASYEDGE_PUBLIC_API TensorRTConfig : public EdgePredictorConfig {
    std::string model_filename{"model"};
    std::string params_filename{"params"};
    std::string cache_name{"m_cache"};
    /**
     * @brief GPU工作空间大小设置
     * workspace_size = workspace_prefix * (1 << workspace_offset)
     * workspace_offset: 10 = KB, 20 = MB, 30 = GB
     */
    int workspace_prefix{100};
    int workspace_offset{20};
    /**
     * @brief 生成最大 batch_size 为 max_batch_size 的优化模型，单次预测图片数量可以小于或等于此值
     */
    int max_batch_size{1};
    /**
     * @brief 设置使用哪张 GPU 卡
     */
    int device{0};
    /**
     * @brief 模型编译等级
     * 0：无论当前设置的max_batch_size是多少，仅使用历史编译产出（如果存在）
     * 1：如果当前max_batch_size与历史编译产出的max_batch_size不相等时，则重新编译模型（推荐）
     * 2：无论历史编译产出的max_batch_size为多少，均根据当前max_batch_size重新编译模型
     */
    int compile_level{1};
    /**
     * @brief 设置device对应的卡可以支持的最大并发量
     * 实际预测的时候对应卡的最大并发量不超过这里设置的范围
     */
    int max_concurrency{1};
    /**
     * @brief 是否开启fp16模式预测，需要硬件支持
     */
    bool fp16{false};
    /**
     * @brief 设置需要使用的DLA Core
     */
    int dla_core{-1};
};

struct EDGE_CONFIG_DEPRECATED EASYEDGE_PUBLIC_API NNIEConfig : public EdgePredictorConfig {
    // 分类模型获取置信度最高的结果数量，topn越大排序耗时越多
    int topn{5};
    // 预测使用的nnie核心，参考NNIE核心数设置。如3559AV100可以设置为0，1。3519A可以设置为0
    int nnie_core_id{0};

};

struct EDGE_CONFIG_DEPRECATED EASYEDGE_PUBLIC_API AtlasConfig : public EdgePredictorConfig {
    int batch_size{1}; // 一次调用推理几张图片，一般用1即可。 使用batch为4的一般可以节省耗时1/4, 但是副作用是：如果只输入1张图，那么推理耗时和4张图一样
    int engine_thread{2}; // ai 引擎的线程数，一般2或4， 如果没有并发推理需要，改为1
    std::string model_name{"params"}; // 模型文件名， 注意每个batch 有对应的模型名。如params-batch4； params的batch为1

    std::string engine_config{"graph.prototxt"}; // 引擎配置，正常情况不要修改
    std::string hiai_resource_list_file{"status.h.list"}; // atlas错误码文件，正常情况不要修改

    // infer_async异步接口使用。AsyncResultHandler 回调结果时，是否需要resized后的图片。 开启后返回RGB格式的resized后的cv::Mat。。
    bool is_callback_image{false};

    // infer 同步接口时，从调用接口到获得atlas引擎结果的超时。 默认2000表示如果本次推理耗时超过超时2s，则报错。
    uint infer_wait_timeout_ms{2000};
    int device_id = 0;

    bool log_enable_device = true; // atlas 300生效, 是否打印device侧的info日志
    bool log_enable_infer_info = true; // 每次infer的详细日志, 开启后有略微性能损失, 记录在/var/dlog中, 高并发下建议关闭.
    bool log_enable_infer_debug = false; // 每次infer的详细日志, 开启后有性能损失, 记录在/var/dlog中
    uint _device_max_log_file_size = 1024 * 1024; // atlas 300生效, 日志文件的最大尺寸

    uint64_t _start_seq_id = 1; // 多模型使用，一般不要修改。第一张图的seq_id。

    int _deconstruct_after_atlas_sleep_ms = 500; // 内部参数，Predictor析构里Atlas引擎销毁后。销毁后不会有结果回调。
    uint _debug_infer_timeout_ms = 0; // >0 后, 超过该值耗时的infer会打印出具体信息
};

enum EdgeTrackStat {
    kTrackStatNew = 0,
    kTrackStatTracked = 1,
    kTrackStatLost = 2,
    kTrackStatRemoved = 3,
};

struct EASYEDGE_PUBLIC_API EdgeResultData {
    int index{0};  // 分类结果的index
    std::string label;  // 分类结果的label
    float prob{0};  // 置信度

    // 物体检测、图像分割、姿态估计时才有意义
    float x1, y1, x2, y2;  // (x1, y1): 左上角（姿态估计为point坐标）， （x2, y2): 右下角； 均为0~1的长宽比例值。
    // 物体检测网络 fasterrcnn_sniper
    int im_id{0};
    // 图像分割或者语义分割的模型，该字段才有意义
    // 请注意：图像分割或者语义分割时，以下两个字段会比较大，使用完成之后请及时释放EdgeResultData
    cv::Mat mask;  // 图像分割:0, 1 的mask 语义分割: CV_8UC1格式Mat
    std::string mask_rle;  // Run Length Encoding，游程编码的mask, 图像分割有，语义分割该字段为空

    // 目标追踪模型，该字段才有意义
    int trackid{0};  // 轨迹id
    int frame{0};  // 处于视频中的第几帧
    EdgeTrackStat track_stat{EdgeTrackStat::kTrackStatNew};  // 跟踪状态

    // 姿态估计模型，该字段才有意义
    int point_id{0}; // 关键点的id
    int point_group_id{0}; // 关键点的分组
    std::vector<int> point_pairs; // 与此关键点配对的其他关键点，用于在关键点之间画连线
};

struct EASYEDGE_PUBLIC_API EdgeModelInfo {
    int64_t id;  // 模型ID; 项目ID
    std::string name;
    EdgeModelKind kind;
    float threshold_rec;  // 推荐阈值
};

enum EdgeDataType {
    kUNDEFINED = -1,
    kFLOAT = 0,
    kFLOAT16 = 1,
    kINT8 = 2,
    kINT32 = 3,
    kUINT8 = 4,
    kINT16 = 6,
    kUINT16 = 7,
    kUINT32 = 8,
    kINT64 = 9,
    kUINT64 = 10,
    kDOUBLE = 11,
    kBOOL = 12,
    kSTRING = 13,
};

///
/** 模型推理
 *  infer 接口包含所有模型的预处理、推理、后处理
 *  forward 接口仅做模型推理
 *
 * @brief NOT thread safe.
 */
class EASYEDGE_PUBLIC_API EdgePredictor {
public:
    /**
     * @brief 异步回调的基类
     */
    class AsyncResultHandler {
    public:

        /**
         * @brief 回调接口：成功
         * @param result 识别结果
         * @param img 被识别的图像。格式为 BGR , HWC格式。
         * 计算模式下为摄像头拍摄的图片；
         * 标准模式下为无效
         * @param seq_id 计算模式下为调用异步接口时返回的id；标准模式下为无效值
         * @param user_data 计算模式下为调用异步接口时设置的user_data；标准模式下为NULL
         */
        virtual int on_result(
                std::vector<EdgeResultData> &result,
                cv::Mat &img,
                uint64_t seq_id = 0,
                void *user_data = nullptr
        ) = 0;

        virtual int on_result(
                std::vector<std::vector<EdgeResultData>> &result,
                std::vector<cv::Mat> &images,
                uint64_t seq_id = 0,
                void *user_data = nullptr
        ) = 0;

        virtual int on_error(EdgeStatus code, const std::string &message, void *params) = 0;
    };

public:
    EdgePredictor() = default;

    EdgePredictor(const EdgePredictor &) = delete;

    virtual ~EdgePredictor() = default;

    /**
     * @deprecated use @code EdgePredictor::model_info @endcode instead
     */
    virtual EdgeModelKind model_kind() = 0;

    virtual EdgeModelInfo model_info() = 0;

    /**
     * @brief initialize predictor
     * @return
     */
    virtual int init() = 0;

    EdgePredictor &operator=(const EdgePredictor &) = delete;

    virtual int infer(
            cv::Mat &image, std::vector<float> &result
    );

    //-------------------------------- 同步预测相关接口 --------------------------------//
    /**
     * @brief see:
     * @related infer(cv::Mat & image, EdgeColorFormat origin_color_format, std::vector<EdgeResultData> &result, float threshold)
     */
    virtual int infer(
            cv::Mat &image, std::vector<EdgeResultData> &result
    ) = 0;

    /**
     * @brief see:
     * @related infer(cv::Mat & image, EdgeColorFormat origin_color_format, std::vector<EdgeResultData> &result, float threshold)
     */
    virtual int infer(
            cv::Mat &image, EdgeColorFormat origin_color_format, std::vector<EdgeResultData> &result
    ) = 0;

    /**
     * @brief inference
     * @param image: must be HWC format (opencv default)
     *  images: batcher infer
     * @param origin_color_format: BGR if not supplied
     * @param result
     * @param threshold: recommended threshold (with best mAP) will be used if not supplied
     * @return 0 if success
     */
    virtual int infer(
            cv::Mat &image,
            EdgeColorFormat origin_color_format,
            std::vector<EdgeResultData> &result,
            float threshold
    ) = 0;

    /**
     * @brief see:
     * @related infer(cv::Mat & image, EdgeColorFormat origin_color_format, std::vector<EdgeResultData> &result, float threshold)
     */
    virtual int infer(
            std::vector<cv::Mat> &images,
            std::vector<std::vector<EdgeResultData>> &results
    );

    /**
     * @brief see:
     * @related infer(cv::Mat & image, EdgeColorFormat origin_color_format, std::vector<EdgeResultData> &result, float threshold)
     */
    virtual int infer(
            std::vector<cv::Mat> &images,
            EdgeColorFormat origin_color_format,
            std::vector<std::vector<EdgeResultData>> &results
    );

    /**
     * @brief see:
     * @related infer(cv::Mat & image, EdgeColorFormat origin_color_format, std::vector<EdgeResultData> &result, float threshold)
     */
    virtual int infer(
            std::vector<cv::Mat> &images,
            EdgeColorFormat origin_color_format,
            std::vector<std::vector<EdgeResultData>> &results,
            float threshold
    );

    virtual int infer(
            cv::Mat &image, std::string &json_result
    );

    virtual int infer(
            cv::Mat &image, std::string &json_result, float threshold
    );

    virtual int infer(
            cv::Mat &image, std::string &json_result, int top_k
    );

    virtual int infer(
            cv::Mat &image, std::string &json_result, float threshold, int top_k
    );

    /**
     * @brief 预测一个文件
     * @param file_content 文件内容
     */
    virtual int infer_file(
            const std::string &file_content, int file_decode_flags, std::string &json_result, float threshold, int top_k
    );

//    /**
//     * @brief experimental
//     */
//    virtual int forward(
//            const std::vector<ETensor> &feed, std::vector<ETensor> &fetch
//    );

    //-------------------------------- 异步预测相关接口 --------------------------------//
    /**
     * @brief 设置异步接口的回调
     * @param handler
     * @return
     */
    virtual int set_result_handler(AsyncResultHandler *handler);

    /**
     * @brief 异步预测接口，只支持Xeye、华为Atlas
     * @param image
     * @param threshold
     * @param user_data
     * @return
     */
    virtual int infer_async(
            cv::Mat &image,
            EdgeColorFormat origin_color_format,
            float threshold,
            void *user_data,
            uint64_t &seq_id);

    virtual int infer_async(
            std::vector<cv::Mat> &images,
            EdgeColorFormat origin_color_format,
            float threshold,
            void *user_data,
            uint64_t &seq_id);
};

/**
 * @brief Controller
 */
class EASYEDGE_PUBLIC_API EdgeController {
public:

    /**
     * @note 设置序列号。
     *
     * 如果需要为不同模型设置不同序列号，请使用:
     * @code
     * EdgePredictorConfig::set_config(easyedge::params::PREDICTOR_KEY_SERIAL_NUM, "{你的序列号}")
     * @endcode
     */
    virtual int set_licence_key(const std::string &license) = 0;

    virtual int set_bundle_id(const std::string &bundle_id) = 0;

    /**
     * @deprecated  Use EdgePredictorConfig::set_config(params::CONTROLLER_KEY_SERVER_ADDR, ...) instead
     */
    [[deprecated("Use EdgePredictorConfig::set_config instead")]]
    virtual int set_server_addr(const std::string &host) = 0;

    virtual int set_log_config(const EdgeLogConfig &log_config) = 0;

    template<typename T>
    void set_config(const std::string &key, const T &value);

    template<typename T>
    void set_config(const std::string &key, const T *value);

    template<typename T>
    T get_config(const std::string &key, const T &default_value);

    template<typename T>
    const T *get_config(const std::string &key, const T *default_value);
    template<typename T = std::string>
    T get_config(const std::string &key);

    template<typename ConfigT>
    std::unique_ptr<EdgePredictor> CreateEdgePredictor(const ConfigT &config);

    /**
     * @brief 开启一个简单的demo http服务。
     * 该方法会block直到收到sigint/sigterm。
     * http服务里，图片的解码运行在cpu之上，可能会降低推理速度。
     * @param config
     * @param host
     * @param port
     * @param service_id service_id  user parameter, uri '/get/service_id' will respond this value with 'text/plain'
     * @param instance_num 实例数量，根据内存/显存/时延要求调整
     * @return
     */
    int start_http_server(
            const EdgePredictorConfig &config,
            const std::string &host,
            int port,
            const std::string &service_id,
            int instance_num = 1);
};

extern EASYEDGE_PUBLIC_API EdgeController *global_controller();

}
#endif
