cmake_minimum_required(VERSION 3.28)
project(retool)

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/include/simpleini/)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp
        ${PROJECT_SOURCE_DIR}/lib/json/jsoncpp.cpp
        ${PROJECT_SOURCE_DIR}/include/simpleini/ConvertUTF.c


)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/spdlog/spdlog.lib)
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/json/jsoncpp_static.lib)
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/json/jsoncpp.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/openssl/libcrypto.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/openssl/libssl.lib)
