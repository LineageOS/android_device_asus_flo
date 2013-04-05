/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef _UAPI_MEDIA_MSM_CAM_SENSOR_H
#define _UAPI_MEDIA_MSM_CAM_SENSOR_H
#ifdef MSM_CAMERA_BIONIC
#include <sys/types.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#endif
#include <linux/types.h>
#include <linux/v4l2-mediabus.h>
#include <linux/i2c.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define I2C_SEQ_REG_SETTING_MAX 5
#define I2C_SEQ_REG_DATA_MAX 20
#define MAX_CID 16
#define MSM_SENSOR_MCLK_8HZ 8000000
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define MSM_SENSOR_MCLK_16HZ 16000000
#define MSM_SENSOR_MCLK_24HZ 24000000
#define GPIO_OUT_LOW (0 << 1)
#define GPIO_OUT_HIGH (1 << 1)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define CSI_EMBED_DATA 0x12
#define CSI_RESERVED_DATA_0 0x13
#define CSI_YUV422_8 0x1E
#define CSI_RAW8 0x2A
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define CSI_RAW10 0x2B
#define CSI_RAW12 0x2C
#define CSI_DECODE_6BIT 0
#define CSI_DECODE_8BIT 1
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define CSI_DECODE_10BIT 2
#define CSI_DECODE_DPCM_10_8_10 5
#define MAX_SENSOR_NAME 32
#define MAX_ACT_MOD_NAME_SIZE 32
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define MAX_ACT_NAME_SIZE 32
#define NUM_ACTUATOR_DIR 2
#define MAX_ACTUATOR_SCENARIO 8
#define MAX_ACTUATOR_REGION 5
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define MAX_ACTUATOR_INIT_SET 12
#define MAX_ACTUATOR_REG_TBL_SIZE 8
#define MOVE_NEAR 0
#define MOVE_FAR 1
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_camera_i2c_reg_addr_type {
 MSM_CAMERA_I2C_BYTE_ADDR = 1,
 MSM_CAMERA_I2C_WORD_ADDR,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_camera_i2c_data_type {
 MSM_CAMERA_I2C_BYTE_DATA = 1,
 MSM_CAMERA_I2C_WORD_DATA,
 MSM_CAMERA_I2C_SET_BYTE_MASK,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_CAMERA_I2C_UNSET_BYTE_MASK,
 MSM_CAMERA_I2C_SET_WORD_MASK,
 MSM_CAMERA_I2C_UNSET_WORD_MASK,
 MSM_CAMERA_I2C_SET_BYTE_WRITE_MASK_DATA,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
enum msm_sensor_power_seq_type_t {
 SENSOR_CLK,
 SENSOR_GPIO,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 SENSOR_VREG,
 SENSOR_I2C_MUX,
};
enum msm_sensor_clk_type_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 SENSOR_CAM_MCLK,
 SENSOR_CAM_CLK,
 SENSOR_CAM_CLK_MAX,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_sensor_power_seq_gpio_t {
 SENSOR_GPIO_RESET,
 SENSOR_GPIO_STANDBY,
 SENSOR_GPIO_MAX,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
enum msm_camera_vreg_name_t {
 CAM_VDIG,
 CAM_VIO,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAM_VANA,
 CAM_VAF,
 CAM_VREG_MAX,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_sensor_resolution_t {
 MSM_SENSOR_RES_FULL,
 MSM_SENSOR_RES_QTR,
 MSM_SENSOR_RES_2,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_SENSOR_RES_3,
 MSM_SENSOR_RES_4,
 MSM_SENSOR_RES_5,
 MSM_SENSOR_RES_6,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_SENSOR_RES_7,
 MSM_SENSOR_INVALID_RES,
};
enum sensor_sub_module_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 SUB_MODULE_SENSOR,
 SUB_MODULE_CHROMATIX,
 SUB_MODULE_ACTUATOR,
 SUB_MODULE_EEPROM,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 SUB_MODULE_LED_FLASH,
 SUB_MODULE_STROBE_FLASH,
 SUB_MODULE_CSIPHY,
 SUB_MODULE_CSIPHY_3D,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 SUB_MODULE_CSID,
 SUB_MODULE_CSID_3D,
 SUB_MODULE_MAX,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum csid_cfg_type_t {
 CSID_INIT,
 CSID_CFG,
 CSID_RELEASE,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
enum csiphy_cfg_type_t {
 CSIPHY_INIT,
 CSIPHY_CFG,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CSIPHY_RELEASE,
};
enum camera_vreg_type {
 REG_LDO,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 REG_VS,
 REG_GPIO,
};
struct msm_sensor_power_setting {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum msm_sensor_power_seq_type_t seq_type;
 uint16_t seq_val;
 long config_val;
 uint16_t delay;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 void *data[10];
};
struct msm_sensor_power_setting_array {
 struct msm_sensor_power_setting *power_setting;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t size;
};
struct msm_sensor_id_info_t {
 uint16_t sensor_id_reg_addr;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t sensor_id;
};
struct msm_camera_sensor_slave_info {
 uint16_t slave_addr;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum msm_camera_i2c_reg_addr_type addr_type;
 struct msm_sensor_id_info_t sensor_id_info;
 struct msm_sensor_power_setting_array power_setting_array;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_camera_i2c_reg_array {
 uint16_t reg_addr;
 uint16_t reg_data;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_camera_i2c_reg_setting {
 struct msm_camera_i2c_reg_array *reg_setting;
 uint16_t size;
 enum msm_camera_i2c_reg_addr_type addr_type;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum msm_camera_i2c_data_type data_type;
 uint16_t delay;
};
struct msm_camera_i2c_seq_reg_array {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t reg_addr;
 uint8_t reg_data[I2C_SEQ_REG_DATA_MAX];
 uint16_t reg_data_size;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_camera_i2c_seq_reg_setting {
 struct msm_camera_i2c_seq_reg_array *reg_setting;
 uint16_t size;
 enum msm_camera_i2c_reg_addr_type addr_type;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t delay;
};
struct msm_camera_csid_vc_cfg {
 uint8_t cid;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint8_t dt;
 uint8_t decode_format;
};
struct msm_camera_csid_lut_params {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint8_t num_cid;
 struct msm_camera_csid_vc_cfg *vc_cfg[MAX_CID];
};
struct msm_camera_csid_params {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint8_t lane_cnt;
 uint16_t lane_assign;
 uint8_t phy_sel;
 struct msm_camera_csid_lut_params lut_params;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_camera_csiphy_params {
 uint8_t lane_cnt;
 uint8_t settle_cnt;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t lane_mask;
 uint8_t combo_mode;
};
struct msm_camera_csi2_params {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_camera_csid_params csid_params;
 struct msm_camera_csiphy_params csiphy_params;
};
struct msm_camera_csi_lane_params {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t csi_lane_assign;
 uint16_t csi_lane_mask;
};
struct csi_lane_params_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t csi_lane_assign;
 uint8_t csi_lane_mask;
 uint8_t csi_if;
 uint8_t csid_core[2];
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint8_t csi_phy_sel;
};
struct msm_sensor_info_t {
 char sensor_name[MAX_SENSOR_NAME];
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int32_t session_id;
 int32_t subdev_id[SUB_MODULE_MAX];
};
struct camera_vreg_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 const char *reg_name;
 enum camera_vreg_type type;
 int min_voltage;
 int max_voltage;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int op_mode;
 uint32_t delay;
};
enum camb_position_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 BACK_CAMERA_B,
 FRONT_CAMERA_B,
};
enum camerab_mode_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAMERA_MODE_2D_B = (1<<0),
 CAMERA_MODE_3D_B = (1<<1)
};
struct msm_sensor_init_params {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int modes_supported;
 enum camb_position_t position;
 uint32_t sensor_mount_angle;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct sensorb_cfg_data {
 int cfgtype;
 union {
 struct msm_sensor_info_t sensor_info;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_sensor_init_params sensor_init_params;
 void *setting;
 } cfg;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct csid_cfg_data {
 enum csid_cfg_type_t cfgtype;
 union {
 uint32_t csid_version;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_camera_csid_params *csid_params;
 } cfg;
};
struct csiphy_cfg_data {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum csiphy_cfg_type_t cfgtype;
 union {
 struct msm_camera_csiphy_params *csiphy_params;
 struct msm_camera_csi_lane_params *csi_lane_params;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 } cfg;
};
enum msm_sensor_cfg_type_t {
 CFG_SET_SLAVE_INFO,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CFG_WRITE_I2C_ARRAY,
 CFG_WRITE_I2C_SEQ_ARRAY,
 CFG_POWER_UP,
 CFG_POWER_DOWN,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CFG_SET_STOP_STREAM_SETTING,
 CFG_GET_SENSOR_INFO,
 CFG_GET_SENSOR_INIT_PARAMS,
 CFG_SET_INIT_SETTING,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CFG_SET_RESOLUTION,
 CFG_SET_STOP_STREAM,
 CFG_SET_START_STREAM,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_actuator_cfg_type_t {
 CFG_GET_ACTUATOR_INFO,
 CFG_SET_ACTUATOR_INFO,
 CFG_SET_DEFAULT_FOCUS,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CFG_MOVE_FOCUS,
};
enum actuator_type {
 ACTUATOR_VCM,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 ACTUATOR_PIEZO,
};
enum msm_actuator_data_type {
 MSM_ACTUATOR_BYTE_DATA = 1,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_ACTUATOR_WORD_DATA,
};
enum msm_actuator_addr_type {
 MSM_ACTUATOR_BYTE_ADDR = 1,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_ACTUATOR_WORD_ADDR,
};
struct reg_settings_t {
 uint16_t reg_addr;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t reg_data;
};
struct region_params_t {
 uint16_t step_bound[2];
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t code_per_step;
};
struct damping_params_t {
 uint32_t damping_step;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t damping_delay;
 uint32_t hw_params;
};
struct msm_actuator_move_params_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int8_t dir;
 int8_t sign_dir;
 int16_t dest_step_pos;
 int32_t num_steps;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct damping_params_t *ringing_params;
};
struct msm_actuator_tuning_params_t {
 int16_t initial_code;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t pwd_step;
 uint16_t region_size;
 uint32_t total_steps;
 struct region_params_t *region_params;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_actuator_params_t {
 enum actuator_type act_type;
 uint8_t reg_tbl_size;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t data_size;
 uint16_t init_setting_size;
 uint32_t i2c_addr;
 enum msm_actuator_addr_type i2c_addr_type;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum msm_actuator_data_type i2c_data_type;
 struct msm_actuator_reg_params_t *reg_tbl_params;
 struct reg_settings_t *init_settings;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_actuator_set_info_t {
 struct msm_actuator_params_t actuator_params;
 struct msm_actuator_tuning_params_t af_tuning_params;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_actuator_get_info_t {
 uint32_t focal_length_num;
 uint32_t focal_length_den;
 uint32_t f_number_num;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t f_number_den;
 uint32_t f_pix_num;
 uint32_t f_pix_den;
 uint32_t total_f_dist_num;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t total_f_dist_den;
 uint32_t hor_view_angle_num;
 uint32_t hor_view_angle_den;
 uint32_t ver_view_angle_num;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t ver_view_angle_den;
};
enum af_camera_name {
 ACTUATOR_MAIN_CAM_0,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 ACTUATOR_MAIN_CAM_1,
 ACTUATOR_MAIN_CAM_2,
 ACTUATOR_MAIN_CAM_3,
 ACTUATOR_MAIN_CAM_4,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 ACTUATOR_MAIN_CAM_5,
 ACTUATOR_WEB_CAM_0,
 ACTUATOR_WEB_CAM_1,
 ACTUATOR_WEB_CAM_2,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_actuator_cfg_data {
 int cfgtype;
 uint8_t is_af_supported;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 union {
 struct msm_actuator_move_params_t move;
 struct msm_actuator_set_info_t set_info;
 struct msm_actuator_get_info_t get_info;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum af_camera_name cam_name;
 } cfg;
};
enum msm_actuator_write_type {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_ACTUATOR_WRITE_HW_DAMP,
 MSM_ACTUATOR_WRITE_DAC,
};
struct msm_actuator_reg_params_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum msm_actuator_write_type reg_write_type;
 uint32_t hw_mask;
 uint16_t reg_addr;
 uint16_t hw_shift;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t data_shift;
};
enum msm_camera_led_config_t {
 MSM_CAMERA_LED_OFF,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_CAMERA_LED_LOW,
 MSM_CAMERA_LED_HIGH,
 MSM_CAMERA_LED_INIT,
 MSM_CAMERA_LED_RELEASE,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_camera_led_cfg_t {
 enum msm_camera_led_config_t cfgtype;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define VIDIOC_MSM_SENSOR_CFG   _IOWR('V', BASE_VIDIOC_PRIVATE + 1, struct sensorb_cfg_data)
#define VIDIOC_MSM_SENSOR_RELEASE   _IO('V', BASE_VIDIOC_PRIVATE + 2)
#define VIDIOC_MSM_SENSOR_GET_SUBDEV_ID   _IOWR('V', BASE_VIDIOC_PRIVATE + 3, uint32_t)
#define VIDIOC_MSM_CSIPHY_IO_CFG   _IOWR('V', BASE_VIDIOC_PRIVATE + 4, struct csid_cfg_data)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define VIDIOC_MSM_CSID_IO_CFG   _IOWR('V', BASE_VIDIOC_PRIVATE + 5, struct csiphy_cfg_data)
#define VIDIOC_MSM_ACTUATOR_CFG   _IOWR('V', BASE_VIDIOC_PRIVATE + 6, struct msm_actuator_cfg_data)
#define VIDIOC_MSM_FLASH_LED_DATA_CFG   _IOWR('V', BASE_VIDIOC_PRIVATE + 7, struct msm_camera_led_cfg_t)
#define MSM_V4L2_PIX_FMT_META v4l2_fourcc('M', 'E', 'T', 'A')
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define MSM_V4L2_PIX_FMT_RESERVED_0 v4l2_fourcc('R', 'E', 'S', '0')
#endif

