#ifndef _HEADER_RECON3D_TYPES_H_
#define _HEADER_RECON3D_TYPES_H_

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short int ushort;

typedef void *nrecon_handle_t;
struct nrecon_point3i{
    int x, y, z;
};

struct nrecon_point3f{
    float x, y, z;
};

struct nrecon_quaternionf{
    float w, x, y, z;
};

struct nrecon_pose_t{
    nrecon_quaternionf qua;
    nrecon_point3f translation;
};

struct nrecon_pointcloud_t{
    int n_pt;
    nrecon_point3f *xyz;
    nrecon_point3f *normal;
    nrecon_point3f *rgb;
    uchar *label;
};

struct nrecon_facet_t{
    int n_face;
    nrecon_point3i *tri_index;
};

struct nrecon_mesh_t{
    nrecon_pointcloud_t pts;
    nrecon_facet_t face;
};

// 8 bits depth
enum nrecon_pixel_format{
    GRAY = 0,
    BGR = 1,
    RGB = 2,
    YUV = 3
};

struct nrecon_img_t{
    nrecon_pixel_format format;
    int w, h, ch;
    uchar *data;
};

struct nrecon_depthmap_t{
    int w, h;
    ushort *data;
};

enum nrecon_camera_model_t{
    INVALID = -1,   
    FISHEYE,
    RADIAL,
    FISHEYE624
};

struct nrecon_camera_t{
    nrecon_camera_model_t model;
    int w, h;
    float fx, fy, cx, cy;
    float distortion_params[12]; // TODO
};

#endif