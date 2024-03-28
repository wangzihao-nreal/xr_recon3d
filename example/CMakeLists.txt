find_package(xr_recon3d REQUIRED)
include_directories(${xr_recon3d_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories(${Eigen3_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(example example.cpp)
target_link_libraries(example
xr_recon3d::xr_recon3d
${OpenCV_LIBRARIES}
)

