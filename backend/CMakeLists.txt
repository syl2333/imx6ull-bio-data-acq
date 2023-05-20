set(CMAKE_C_COMPILER "/home/yilongshang/imx_linux/buildroot-2022.02.9/output/host/bin/arm-linux-gcc")
set(CMAKE_CXX_COMPILER "/home/yilongshang/imx_linux/buildroot-2022.02.9/output/host/bin/arm-linux-g++")
set(CMAKE_SYSROOT "/home/yilongshang/imx_linux/buildroot-2022.02.9/output/host/arm-buildroot-linux-gnueabihf/sysroot")
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# set(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
project(imx-backend LANGUAGES CXX)




add_executable(imx-backend src/main.cpp src/db.cpp src/log.cpp src/server.cpp src/uart.cpp)

find_package(SQLite3)
include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries(imx-backend ${SQLite3_LIBRARIES})

# 寻找 log4cpp 库
find_package(PkgConfig)
pkg_check_modules(LOG4CPP REQUIRED log4cpp)
# 将 log4cpp 库的头文件目录添加到项目的 include 路径中
include_directories(${LOG4CPP_INCLUDE_DIRS})
target_link_libraries(imx-backend ${LOG4CPP_LIBRARIES})



find_library(SERIALPORT_LIBRARY serialport)
target_link_libraries(imx-backend ${SERIALPORT_LIBRARY})
# 搜索 nlohmann/json 库
find_package(nlohmann_json REQUIRED)
target_link_libraries(imx-backend  nlohmann_json::nlohmann_json)
target_include_directories(imx-backend PUBLIC ./thirdparty/cpp-httplib/)

find_package(GSL REQUIRED)
target_link_libraries(imx-backend GSL::gsl GSL::gslcblas)