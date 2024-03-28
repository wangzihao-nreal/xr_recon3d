cmake_minimum_required(VERSION 3.23.1 )

project(test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -w")
add_definitions(-DNR_API_EXPORTS)

# Define relative dir for ${CMAKE_SOURCE_DIR}
set(PROJECT_SRC_DIR "example")

set(EXTERNAL_PROJECT_DIR ${PROJECT_SOURCE_DIR}/external/project)
list( APPEND CMAKE_MODULE_PATH "${EXTERNAL_PROJECT_DIR}/cmake" )

option(STATIC_LINK_PLUGINS "Static link plugins. Just for release" OFF)
option(BUILD_PYTHON "build python package for xr_fisheye_rectify" OFF)

set(ENABLE_REL_WITH_DEB_INFO OFF)
# After set environment variable, we includ project cmake..
include(Project)

# Set git hook
execute_process(COMMAND git config core.hooksPath external/project/githook)