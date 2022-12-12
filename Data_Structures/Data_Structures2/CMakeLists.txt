cmake_minimum_required(VERSION 3.10)
project(blockchain)

add_executable(blockchain main.c)

add_library(mtwister STATIC ${CMAKE_SOURCE_DIR}/libs/mtwister.c)
target_link_libraries(blockchain mtwister)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})