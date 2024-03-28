#ifndef __HEADER_RECON3D_DEF_H_
#define __HEADER_RECON3D_DEF_H_

#include "Recon3D_def.h"
#include "Recon3D_types.h"

enum struct nrecon_fusion_mode_t{
    DEPTH = 0,
    DEPTH_SEMANTIC = 1,
    DEPTH_COLOR = 2
};

struct nrecon_option_t
{
    nrecon_fusion_mode_t mode;
    nrecon_camera_t color_cam, depth_cam;
    nrecon_pose_t Tcd;
    float voxel_size;
    float trunc_dist;
    float min_depth;
    float max_depth;
};

struct nrecon_input_t {
  nrecon_pose_t pose;          
  nrecon_depthmap_t depth;   
  nrecon_img_t color_img;     
  nrecon_img_t semantic_img; 
};

NR_API(int) nrecon_create_handle(nrecon_handle_t *handle, nrecon_option_t option);

NR_API(int) nrecon_destroy_handle(nrecon_handle_t handle);

NR_API(int) nrecon_process(nrecon_handle_t handle, nrecon_input_t input);

NR_API(int) nrecon_get_mesh(nrecon_handle_t handle, nrecon_mesh_t *mesh);

NR_API(int) nrecon_release_mesh(nrecon_mesh_t *mesh);

#endif