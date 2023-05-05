cmake_minimum_required(VERSION 3.5)
project(imx-backend LANGUAGES CXX)






add_executable(imx-backend src/main.cpp src/db.cpp src/log.cpp)

find_package(SQLite3)
include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries(imx-backend ${SQLite3_LIBRARIES})

# 寻找 log4cpp 库
find_package(PkgConfig)
pkg_check_modules(LOG4CPP REQUIRED log4cpp)
# 将 log4cpp 库的头文件目录添加到项目的 include 路径中
include_directories(${LOG4CPP_INCLUDE_DIRS})
target_link_libraries(imx-backend ${LOG4CPP_LIBRARIES})

target_include_directories(imx-backend PUBLIC ./thirdparty/cpp-httplib/)
