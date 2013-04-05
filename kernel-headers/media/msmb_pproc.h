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
#ifndef __MSMB_PPROC_H
#define __MSMB_PPROC_H
#ifdef MSM_CAMERA_BIONIC
#include <sys/types.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#endif
#include <linux/videodev2.h>
#include <linux/types.h>
#define MAX_PLANES VIDEO_MAX_PLANES
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define MAX_NUM_CPP_STRIPS 8
enum msm_cpp_frame_type {
 MSM_CPP_OFFLINE_FRAME,
 MSM_CPP_REALTIME_FRAME,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_cpp_frame_strip_info {
 int scale_v_en;
 int scale_h_en;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int upscale_v_en;
 int upscale_h_en;
 int src_start_x;
 int src_end_x;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int src_start_y;
 int src_end_y;
 int pad_bottom;
 int pad_top;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int pad_right;
 int pad_left;
 int v_init_phase;
 int h_init_phase;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int h_phase_step;
 int v_phase_step;
 int prescale_crop_width_first_pixel;
 int prescale_crop_width_last_pixel;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int prescale_crop_height_first_line;
 int prescale_crop_height_last_line;
 int postscale_crop_height_first_line;
 int postscale_crop_height_last_line;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int postscale_crop_width_first_pixel;
 int postscale_crop_width_last_pixel;
 int dst_start_x;
 int dst_end_x;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int dst_start_y;
 int dst_end_y;
 int bytes_per_pixel;
 unsigned int source_address;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 unsigned int destination_address;
 unsigned int src_stride;
 unsigned int dst_stride;
 int rotate_270;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int horizontal_flip;
 int vertical_flip;
 int scale_output_width;
 int scale_output_height;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int prescale_crop_en;
 int postscale_crop_en;
};
struct msm_cpp_frame_info_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int32_t frame_id;
 uint32_t inst_id;
 uint32_t client_id;
 enum msm_cpp_frame_type frame_type;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t num_strips;
 struct msm_cpp_frame_strip_info *strip_info;
 uint32_t msg_len;
 uint32_t *cpp_cmd_msg;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int src_fd;
 int dst_fd;
 struct ion_handle *src_ion_handle;
 struct ion_handle *dest_ion_handle;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct cpp_hw_info {
 uint32_t cpp_hw_version;
 uint32_t cpp_hw_caps;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
#define VIDIOC_MSM_CPP_CFG   _IOWR('V', BASE_VIDIOC_PRIVATE, struct msm_camera_v4l2_ioctl_t)
#define VIDIOC_MSM_CPP_GET_EVENTPAYLOAD   _IOWR('V', BASE_VIDIOC_PRIVATE + 1, struct msm_camera_v4l2_ioctl_t)
#define VIDIOC_MSM_CPP_GET_INST_INFO   _IOWR('V', BASE_VIDIOC_PRIVATE + 2, struct msm_camera_v4l2_ioctl_t)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define VIDIOC_MSM_CPP_LOAD_FIRMWARE   _IOWR('V', BASE_VIDIOC_PRIVATE + 3, struct msm_camera_v4l2_ioctl_t)
#define VIDIOC_MSM_CPP_GET_HW_INFO   _IOWR('V', BASE_VIDIOC_PRIVATE + 4, struct msm_camera_v4l2_ioctl_t)
#define VIDIOC_MSM_CPP_FLUSH_QUEUE   _IOWR('V', BASE_VIDIOC_PRIVATE + 5, struct msm_camera_v4l2_ioctl_t)
#define V4L2_EVENT_CPP_FRAME_DONE (V4L2_EVENT_PRIVATE_START + 0)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_camera_v4l2_ioctl_t {
 uint32_t id;
 uint32_t len;
 uint32_t trans_code;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 void __user *ioctl_ptr;
};
#endif

