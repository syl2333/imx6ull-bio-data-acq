cmake_minimum_required(VERSION 3.5)
project(imx-backend LANGUAGES CXX)



find_package(SQLite3)
include_directories(${SQLITE3_INCLUDE_DIRS})


add_executable(imx-backend src/main.cpp src/db.cpp)
# target_link_libraries(imx-backend SQLite3)
target_link_libraries(imx-backend ${SQLite3_LIBRARIES})

target_include_directories(imx-backend PUBLIC ./thirdparty/cpp-httplib/)
