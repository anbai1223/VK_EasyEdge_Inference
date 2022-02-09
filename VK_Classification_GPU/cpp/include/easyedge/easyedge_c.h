#ifndef EASYEDGE_EASYEDGE_C_H
#define EASYEDGE_EASYEDGE_C_H

#include <stdint.h>
#include <stdbool.h>

#ifndef EASYEDGE_C_PUBLIC_API
#define EASYEDGE_C_PUBLIC_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef const char cchar_t;

/**
 * @brief 获取最后的错误详情
 * @param [out] error   错误详情字符串
 * @param [out] length  错误详情字符串长度
 * @retval      0       成功
 * @retval      !=0     失败
 */
EASYEDGE_C_PUBLIC_API int get_last_error_detail(char *error, uint64_t *length);

/// ----------------- 以下为字符串辅助结构 --------------------   ////
typedef struct EdgeString EdgeString_t;

/**
 * @brief 创建新的字符串辅助结构
 * @return 新的字符串辅助结构的指针
 */
EASYEDGE_C_PUBLIC_API EdgeString_t *create_edge_string();

/**
 * @brief 销毁字符串辅助结构
 * @param [in] edge_log_config 字符串辅助结构的指针
 */
EASYEDGE_C_PUBLIC_API void destroy_edge_string(EdgeString_t *edge_string);

/**
 * @brief 获取字符串数据
 * @param [in]  edge_string 字符串辅助结构的指针
 * @param [out] content     指向内容地址的指针
 * @param [out] length      内容长度
 * @retval      0           成功
 * @retval      !=0         失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_string_get_content(EdgeString_t *edge_string, cchar_t **content, uint64_t *length);

/**
 * @brief 设置字符串数据
 * @param [in]  edge_string 字符串辅助结构的指针
 * @param [in]  content     内容指针
 * @param [in]  length      内容长度
 * @retval      0           成功
 * @retval      !=0         失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_string_set_content(EdgeString_t *edge_string, char *content, uint64_t length);

/// ----------------- 以下为日志的配置项 --------------------   ////
typedef struct EdgeLogConfig EdgeLogConfig_t;

/**
 * @brief 创建新的日志配置
 * @return 新的日志配置的指针
 */
EASYEDGE_C_PUBLIC_API EdgeLogConfig_t *create_edge_log_config();

/**
 * @brief 销毁日志配置
 * @param [in]  edge_log_config 日志配置的指针
 */
EASYEDGE_C_PUBLIC_API void destroy_edge_log_config(EdgeLogConfig_t *edge_log_config);

/**
 * @brief 获取日志配置是否打印debug级别的日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [out] enable_debug    是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_get_enable_debug(EdgeLogConfig_t *edge_log_config, bool *enable_debug);

/**
 * @brief 设置日志配置是否打印debug级别的日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [in]  enable_debug    是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_set_enable_debug(EdgeLogConfig_t *edge_log_config, bool enable_debug);

/**
 * @brief 获取日志配置是否打印info级别的日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [out] enable_info     是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_get_enable_info(EdgeLogConfig_t *edge_log_config, bool *enable_info);

/**
 * @brief 设置日志配置是否打印info级别的日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [in]  enable_info     是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_set_enable_info(EdgeLogConfig_t *edge_log_config, bool enable_info);

/**
 * @brief 获取日志配置是否打印warning级别的日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [out] enable_warning  是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_get_enable_warning(EdgeLogConfig_t *edge_log_config, bool *enable_warning);

/**
 * @brief 设置日志配置是否打印warning级别的日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [in]  enable_warning  是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_set_enable_warning(EdgeLogConfig_t *edge_log_config, bool enable_warning);

/**
 * @brief 获取日志配置是否向文件输出日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [out] to_file         是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_get_to_file(EdgeLogConfig_t *edge_log_config, bool *to_file);

/**
 * @brief 设置日志配置是否向文件输出日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [in]  to_file         是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_set_to_file(EdgeLogConfig_t *edge_log_config, bool to_file);

/**
 * @brief 获取日志配置是否向标准输出输出日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [out] to_std          是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_get_to_std(EdgeLogConfig_t *edge_log_config, bool *to_std);

/**
 * @brief 设置日志配置是否向标准输出输出日志
 * @param [in]  edge_log_config 日志配置的指针
 * @param [in]  to_std          是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_set_to_std(EdgeLogConfig_t *edge_log_config, bool to_std);

/**
 * @brief 获取日志配置是否向标准输出输出日志时带颜色
 * @param [in]  edge_log_config 日志配置的指针
 * @param [out] to_std_color    是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_get_to_std_colorful(EdgeLogConfig_t *edge_log_config, bool *to_std_color);

/**
 * @brief 设置日志配置是否向标准输出输出日志时带颜色
 * @param [in]  edge_log_config 日志配置的指针
 * @param [in]  to_std_color    是否开启
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_set_to_std_colorful(EdgeLogConfig_t *edge_log_config, bool to_std_colorful);

/**
 * @brief 获取日志配置向文件输出日志时文件的最大大小
 * @param [in]  edge_log_config     日志配置的指针
 * @param [out] max_log_file_size   大小，单位B
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_get_max_log_file_size(EdgeLogConfig_t *edge_log_config,
                                                                uint32_t *max_log_file_size);

/**
 * @brief 设置日志配置向文件输出日志时文件的最大大小
 * @param [in]  edge_log_config     日志配置的指针
 * @param [in]  max_log_file_size   大小，单位B
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_set_max_log_file_size(EdgeLogConfig_t *edge_log_config,
                                                                uint32_t max_log_file_size);

/**
 * @brief 获取日志配置向文件输出日志时文件的路径
 * @param [in]  edge_log_config 日志配置的指针
 * @param [out] log_file_path   文件路径
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_get_log_file_path(EdgeLogConfig_t *edge_log_config,
                                                            EdgeString_t *log_file_path);

/**
 * @brief 设置日志配置向文件输出日志时文件的路径
 * @param [in]  edge_log_config 日志配置的指针
 * @param [in]  log_file_path   文件路径
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_log_config_set_log_file_path(EdgeLogConfig_t *edge_log_config,
                                                            EdgeString_t *log_file_path);

/// ----------------- 以下为预测的配置项 --------------------   ////
typedef struct EdgePredictorConfig EdgePredictorConfig_t;

/**
 * @brief 创建新的预测配置
 * @return 新的预测配置的指针
 */
EASYEDGE_C_PUBLIC_API EdgePredictorConfig_t *create_edge_predictor_config();

/**
 * @brief 销毁预测配置
 * @param [in]  edge_predictor_config   预测配置的指针
 */
EASYEDGE_C_PUBLIC_API void destroy_edge_predictor_config(EdgePredictorConfig_t *edge_predictor_config);

/**
 * @brief 获取预测配置的模型目录路径
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [out] model_dir               模型目录路径
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_get_model_dir(EdgePredictorConfig_t *edge_predictor_config,
                                                              EdgeString_t *model_dir);
/**
 * @brief 设置预测配置的模型目录路径
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  model_dir               模型目录路径
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_set_model_dir(EdgePredictorConfig_t *edge_predictor_config,
                                                              EdgeString_t *model_dir);
/**
 * @brief 以bool类型获取预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [out] config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_get_as_bool(EdgePredictorConfig_t *edge_predictor_config,
                                                            EdgeString_t *config_name,
                                                            bool *config_value);

/**
 * @brief 以bool类型设置预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [in]  config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_set_as_bool(EdgePredictorConfig_t *edge_predictor_config,
                                                            EdgeString_t *config_name,
                                                            bool config_value);

/**
 * @brief 以int类型获取预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [out] config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_get_as_int(EdgePredictorConfig_t *edge_predictor_config,
                                                           EdgeString_t *config_name,
                                                           int *config_value);

/**
 * @brief 以int类型设置预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [in]  config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_set_as_int(EdgePredictorConfig_t *edge_predictor_config,
                                                           EdgeString_t *config_name,
                                                           int config_value);

/**
 * @brief 以unsigned int类型获取预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [out] config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_get_as_uint(EdgePredictorConfig_t *edge_predictor_config,
                                                            EdgeString_t *config_name,
                                                            unsigned int *config_value);

/**
 * @brief 以unsigned int类型设置预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [in]  config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_set_as_uint(EdgePredictorConfig_t *edge_predictor_config,
                                                            EdgeString_t *config_name,
                                                            unsigned int config_value);

/**
 * @brief 以long类型获取预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [out] config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_get_as_long(EdgePredictorConfig_t *edge_predictor_config,
                                                            EdgeString_t *config_name,
                                                            long *config_value);

/**
 * @brief 以long类型设置预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [in]  config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_set_as_long(EdgePredictorConfig_t *edge_predictor_config,
                                                            EdgeString_t *config_name,
                                                            long config_value);

/**
 * @brief 以unsigned long类型获取预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [out] config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_get_as_ulong(EdgePredictorConfig_t *edge_predictor_config,
                                                             EdgeString_t *config_name,
                                                             unsigned long *config_value);

/**
 * @brief 以unsigned long类型设置预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [in]  config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_set_as_ulong(EdgePredictorConfig_t *edge_predictor_config,
                                                             EdgeString_t *config_name,
                                                             unsigned long config_value);

/**
 * @brief 以float类型获取预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [out] config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_get_as_float(EdgePredictorConfig_t *edge_predictor_config,
                                                             EdgeString_t *config_name,
                                                             float *config_value);

/**
 * @brief 以float类型设置预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [in]  config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_set_as_float(EdgePredictorConfig_t *edge_predictor_config,
                                                             EdgeString_t *config_name,
                                                             float config_value);

/**
 * @brief 以double类型获取预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [out] config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_get_as_double(EdgePredictorConfig_t *edge_predictor_config,
                                                              EdgeString_t *config_name,
                                                              double *config_value);

/**
 * @brief 以double类型设置预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [in]  config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_set_as_double(EdgePredictorConfig_t *edge_predictor_config,
                                                              EdgeString_t *config_name,
                                                              double config_value);

/**
 * @brief 以字符串类型获取预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [out] config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_get_as_string(EdgePredictorConfig_t *edge_predictor_config,
                                                              EdgeString_t *config_name,
                                                              EdgeString_t *config_value);

/**
 * @brief 以字符串类型设置预测指定配置项
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  config_name             配置项名，可参考 xxx_config.h 中的常量说明
 * @param [in]  config_value            配置项值
 * @retval      0                       成功
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_config_set_as_string(EdgePredictorConfig_t *edge_predictor_config,
                                                              EdgeString_t *config_name,
                                                              EdgeString_t *config_value);

/// ----------------- 以下为预测器 --------------------   ////
typedef struct EdgePredictor EdgePredictor_t;

/**
 * @brief 预测器初始化
 * @param [in]  edge_predictor  预测器的指针
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_init(EdgePredictor_t *edge_predictor);

/**
 * @brief 预测，以json格式返回
 * @param [in]  edge_predictor  预测器的指针
 * @param [in]  img_array       图片的二进制数据
 * @param [in]  img_length      图片的二进制长度
 * @param [in]  imread_flag     图片的解码flag，参考opencv的imread的flag
 * @param [out] result          预测结果的数据，语义分割为mask的png二进制格式，其他为json格式
 * @param [in]  threshold       阈值，0-1之间
 * @param [in]  top_k           结果最大数量
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_infer(EdgePredictor_t *edge_predictor,
                                               const char *img_array, uint64_t img_length,
                                               int imread_flag,
                                               EdgeString_t *result,
                                               float threshold,
                                               int top_k);

/**
 * @brief 获取模型ID
 * @param [in]  edge_predictor  预测器的指针
 * @param [out] model_id        模型ID
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_get_model_id(EdgePredictor_t *edge_predictor,
                                                      int64_t *model_id);

/**
 * @brief 获取模型名
 * @param [in]  edge_predictor  预测器的指针
 * @param [out] model_name      模型名
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_get_model_name(EdgePredictor_t *edge_predictor,
                                                        EdgeString_t *model_name);

/**
 * @brief 获取模型类型
 * @param [in]  edge_predictor  预测器的指针
 * @param [out] model_kind      模型类型
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_get_model_kind(EdgePredictor_t *edge_predictor,
                                                        int *model_kind);

/**
 * @brief 获取模型推荐阈值
 * @param [in]  edge_predictor  预测器的指针
 * @param [out] model_kind      模型推荐阈值
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_predictor_get_model_threshold_rec(EdgePredictor_t *edge_predictor,
                                                                 float *threshold_rec);

/// ----------------- 以下为主控的配置项 --------------------   ////
typedef struct EdgeController EdgeController_t;

/**
 * @brief 创建新的主控
 * @return 新的主控的指针
 */
EASYEDGE_C_PUBLIC_API EdgeController_t *create_edge_controller();

/**
 * @brief 销毁主控
 * @param [in]  edge_controller 主控的指针
 */
EASYEDGE_C_PUBLIC_API void destroy_edge_controller(EdgeController_t *edge_controller);

/**
 * @brief 设置日志配置
 * @param [in] edge_controller  主控的指针
 * @param [in] edge_log_config  日志配置的指针
 * @retval      0               成功
 * @retval      !=0             失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_set_log_config(EdgeController_t *edge_controller,
                                                         EdgeLogConfig_t *edge_log_config);

/**
 * @brief 以bool类型获取主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [out] config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_get_as_bool(EdgeController_t *edge_controller,
                                                             EdgeString_t *config_name,
                                                             bool *config_value);

/**
 * @brief 以bool类型设置主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [in]  config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_set_as_bool(EdgeController_t *edge_controller,
                                                             EdgeString_t *config_name,
                                                             bool config_value);

/**
 * @brief 以int类型获取主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [out] config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_get_as_int(EdgeController_t *edge_controller,
                                                            EdgeString_t *config_name,
                                                            int *config_value);

/**
 * @brief 以int类型设置主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [in]  config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_set_as_int(EdgeController_t *edge_controller,
                                                            EdgeString_t *config_name,
                                                            int config_value);

/**
 * @brief 以unsigned int类型获取主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [out] config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_get_as_uint(EdgeController_t *edge_controller,
                                                             EdgeString_t *config_name,
                                                             unsigned int *config_value);

/**
 * @brief 以unsigned int类型设置主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [in]  config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_set_as_uint(EdgeController_t *edge_controller,
                                                             EdgeString_t *config_name,
                                                             unsigned int config_value);

/**
 * @brief 以long类型获取主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [out] config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_get_as_long(EdgeController_t *edge_controller,
                                                             EdgeString_t *config_name,
                                                             long *config_value);

/**
 * @brief 以long类型设置主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [in]  config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_set_as_long(EdgeController_t *edge_controller,
                                                             EdgeString_t *config_name,
                                                             long config_value);

/**
 * @brief 以unsigned long类型获取主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [out] config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_get_as_ulong(EdgeController_t *edge_controller,
                                                              EdgeString_t *config_name,
                                                              unsigned long *config_value);

/**
 * @brief 以unsigned long类型设置主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [in]  config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_set_as_ulong(EdgeController_t *edge_controller,
                                                              EdgeString_t *config_name,
                                                              unsigned long config_value);
/**
 * @brief 以float类型获取主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [out] config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_get_as_float(EdgeController_t *edge_controller,
                                                              EdgeString_t *config_name,
                                                              float *config_value);

/**
 * @brief 以float类型设置主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [in]  config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_set_as_float(EdgeController_t *edge_controller,
                                                              EdgeString_t *config_name,
                                                              float config_value);

/**
 * @brief 以double类型获取主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [out] config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_get_as_double(EdgeController_t *edge_controller,
                                                               EdgeString_t *config_name,
                                                               double *config_value);

/**
 * @brief 以double类型设置主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [in]  config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_set_as_double(EdgeController_t *edge_controller,
                                                               EdgeString_t *config_name,
                                                               double config_value);

/**
 * @brief 以字符串类型获取主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [out] config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_get_as_string(EdgeController_t *edge_controller,
                                                               EdgeString_t *config_name,
                                                               EdgeString_t *config_value);

/**
 * @brief 以字符串类型设置主控指定配置项
 * @param [in]  edge_controller     主控的指针
 * @param [in]  config_name         配置项名
 * @param [in]  config_value        配置项值
 * @retval      0                   成功
 * @retval      !=0                 失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_config_set_as_string(EdgeController_t *edge_controller,
                                                               EdgeString_t *config_name,
                                                               EdgeString_t *config_value);

/**
 * @brief 创建预测器
 * @param [in] edge_controller          主控的指针
 * @param [in] edge_predictor_config    预测配置的指针
 * @return 新的预测器的指针
 */
EASYEDGE_C_PUBLIC_API EdgePredictor_t *edge_controller_create_predictor(EdgeController_t *edge_controller,
                                                                        EdgePredictorConfig_t *edge_predictor_config);

/**
 * @brief 销毁预测器
 * @param [in]  edge_controller 主控的指针
 * @param [in]  edge_predictor  预测器的指针
 */
EASYEDGE_C_PUBLIC_API void edge_controller_destroy_predictor(EdgeController_t *edge_controller,
                                                             EdgePredictor_t *edge_predictor);

/**
 * @brief 开启http服务，开启成功会保持阻塞状态直到收到sigint/sigterm或收到stop请求
 * @param [in]  edge_controller         主控的指针
 * @param [in]  edge_predictor_config   预测配置的指针
 * @param [in]  host                    监听地址字符串 e.g. 127.0.0.1 or 0.0.0.0 or other
 * @param [in]  port                    端口
 * @param [in]  service_id              服务标识字符串
 * @param [in]  instance_num            实例数量，根据内存/显存/时延要求调整
 * @retval      0                       正常退出
 * @retval      !=0                     失败，可通过 get_last_error_detail 获取详情
 */
EASYEDGE_C_PUBLIC_API int edge_controller_start_http_server(EdgeController_t *edge_controller,
                                                            EdgePredictorConfig_t *edge_predictor_config,
                                                            EdgeString_t *host,
                                                            int port,
                                                            EdgeString_t *service_id,
                                                            int instance_num);

#ifdef __cplusplus
}
#endif

#endif //EASYEDGE_EASYEDGE_C_H
