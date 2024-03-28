#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "Recon3D.h"

void loadOption(nrecon_option_t& options)
{
   // 融合相关
   options.mode = nrecon_fusion_mode_t::DEPTH_COLOR;
   options.voxel_size = 0.01;
   options.trunc_dist = 0.04;
   options.min_depth = 0.2;
   options.max_depth = 4;

   // 相机模型
   options.depth_cam.model = nrecon_camera_model_t::RADIAL;
   options.depth_cam.w = 640;
   options.depth_cam.h = 576;
   options.depth_cam.fx = 505;
   options.depth_cam.fy = 505;
   options.depth_cam.cx = 333;
   options.depth_cam.cy = 323;

   std::vector<float> depthdist = {0.4601059854030609, 0.07308000326156616, 6.500000017695129e-05, 0.00011000000085914508,
           0.004455000162124634, 0.8008930087089539, 0.15987099707126617, 0.020755000412464142};
   memcpy(options.color_cam.distortion_params, (void*)depthdist.data(), 8*sizeof(float));
   
   options.color_cam.model = nrecon_camera_model_t::FISHEYE624;
   options.color_cam.w = 480;
   options.color_cam.h = 640;
   options.color_cam.fx = 240;
   options.color_cam.fy = 240;
   options.color_cam.cx = 236;
   options.color_cam.cy = 317;

   std::vector<float> colordist = {2.1206784671447799e-02, 2.4608268341964609e-02, -2.7478220593848159e-02, 5.9053966965605421e-03};
   memcpy(options.color_cam.distortion_params, (void*)colordist.data(), 4*sizeof(float));

    Eigen::Matrix4f Tcd;
    Tcd  << 0.992468, -0.000590151, 0.122496, 0.0228532,
            -0.00180154, 0.99981, 0.0194134, 0.0661714,
            -0.122484, -0.0194876, 0.992279, -0.000999663,
            0, 0, 0, 1;
    Eigen::Quaternionf q(Tcd.block<3, 3>(0, 0));
    Eigen::Vector3f t(Tcd.block<3, 1>(0, 3));
    options.Tcd.qua.w = q.w();
    options.Tcd.qua.x = q.x();
    options.Tcd.qua.y = q.y();
    options.Tcd.qua.z = q.z();
    options.Tcd.translation.x = t.x();
    options.Tcd.translation.y = t.y();
    options.Tcd.translation.z = t.z();

}

void loadInput(cv::Mat& depth, cv::Mat& color, cv::Mat& pose, nrecon_input_t& input){
    // depth
    input.depth.w = depth.cols;
    input.depth.h = depth.rows;
    input.depth.data = (ushort*)depth.data;

    // color | label
    input.color_img.w = color.cols;
    input.color_img.h = color.rows;
    input.color_img.ch = 3;  // 语义图则为1
    input.color_img.data = (uchar*)color.data;

    // pose
    Eigen::Matrix4f T = Eigen::Matrix4f::Identity();
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            T(i, j) = pose.at<float>(i, j);
    Eigen::Quaternionf q(T.block<3, 3>(0, 0));
    Eigen::Vector3f t(T.block<3, 1>(0, 3));

    input.pose.qua = {q.w(), q.x(), q.y(), q.z()};
    input.pose.translation = {t.x(), t.y(), t.z()};
}

int main()
{
    nrecon_handle_t handle;
    nrecon_option_t option;
    loadOption(option);                         // 加载参数
    nrecon_create_handle(&handle, option);      // 创建深度融合实例

    while(1)                                    // 主循环
    {
        cv::Mat depth, color, pose;
        nrecon_input_t input;
        /*
            Todo：读取数据
        */
        loadInput(depth, color, pose, input);

        nrecon_process(handle, input);          // 深度融合部分
    }

    nrecon_mesh_t mesh;                         // 创建mesh实例
    nrecon_get_mesh(handle, &mesh);             // 提取mesh
    nrecon_release_mesh(&mesh);                 // 释放mesh

    nrecon_destroy_handle(handle);              // 释放深度融合实例
    return 0;
}