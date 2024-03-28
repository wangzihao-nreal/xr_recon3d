# XR Recon3D

## 说明

1. camera_model: 详见camera-model <br>
a. INVLID模式为无需去畸变处理。<br>
b. 语义图去畸变处理和彩色图相同，其内参需要赋值给color_cam

2. fusion_mode <br>
a. DEPTH需要提供深度图，DETPH_SEMANTIC需要同时提供深度图和语义图， DEPTH_COLOR需要同时提供深度图和彩色图 <br>
b. DEPTH_SEMANTIC和DEPTH_COLOR模式需要提供深度图和彩色图(语义图)的外参，如果已经对齐则给一个单位矩阵
 
3. depthmap <br>
深度图为ushort类型，单位为mm，需要传入w, h和ushort类型的图像数据指针

4. colorimg | labelimg <br>
均为uchar类型，需要传入ch, w, h和uchar类型的数据指针，如果不输入彩色图或语义图则不需要处理


## 示例代码
### C++
详见example.cpp

## 其他项目中依赖
- 在conanfile.py中添加：
```Bash
self.requires("xr_recon3d/develop", transitive_libs=True)
```
- CMakeLists.txt中添加：
```CMake
find_package(xr_recon3d REQUIRED)
include_directories(${xr_recon3d_INCLUDE_DIRS})

...

target_link_libraries(xxx xr_recon3d::xr_recon3d)
```
