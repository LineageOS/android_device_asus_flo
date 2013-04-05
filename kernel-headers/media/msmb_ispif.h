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
#ifndef MSM_CAM_ISPIF_H
#define MSM_CAM_ISPIF_H
#define CSID_VERSION_V2 0x02000011
#define CSID_VERSION_V3 0x30000000
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_ispif_vfe_intf {
 VFE0,
 VFE1,
 VFE_MAX
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
#define VFE0_MASK (1 << VFE0)
#define VFE1_MASK (1 << VFE1)
enum msm_ispif_intftype {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 PIX0,
 RDI0,
 PIX1,
 RDI1,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 RDI2,
 INTF_MAX
};
#define PIX0_MASK (1 << PIX0)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define PIX1_MASK (1 << PIX1)
#define RDI0_MASK (1 << RDI0)
#define RDI1_MASK (1 << RDI1)
#define RDI2_MASK (1 << RDI2)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_ispif_vc {
 VC0,
 VC1,
 VC2,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VC3,
 VC_MAX
};
enum msm_ispif_cid {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CID0,
 CID1,
 CID2,
 CID3,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CID4,
 CID5,
 CID6,
 CID7,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CID8,
 CID9,
 CID10,
 CID11,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CID12,
 CID13,
 CID14,
 CID15,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CID_MAX
};
enum msm_ispif_csid {
 CSID0,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CSID1,
 CSID2,
 CSID3,
 CSID_MAX
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_ispif_params_entry {
 enum msm_ispif_intftype intftype;
 int num_cids;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum msm_ispif_cid cids[3];
 enum msm_ispif_csid csid;
};
struct msm_ispif_param_data {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum msm_ispif_vfe_intf vfe_intf;
 uint32_t num;
 struct msm_ispif_params_entry entries[INTF_MAX];
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum ispif_cfg_type_t {
 ISPIF_CLK_ENABLE,
 ISPIF_CLK_DISABLE,
 ISPIF_INIT,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 ISPIF_CFG,
 ISPIF_START_FRAME_BOUNDARY,
 ISPIF_STOP_FRAME_BOUNDARY,
 ISPIF_STOP_IMMEDIATELY,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 ISPIF_RELEASE,
 ISPIF_ENABLE_REG_DUMP,
};
struct ispif_cfg_data {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum ispif_cfg_type_t cfg_type;
 union {
 int reg_dump;
 uint32_t csid_version;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_ispif_param_data params;
 };
};
#define VIDIOC_MSM_ISPIF_CFG   _IOWR('V', BASE_VIDIOC_PRIVATE, struct ispif_cfg_data)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#endif

