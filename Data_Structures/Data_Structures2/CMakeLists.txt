cmake_minimum_required(VERSION 3.10)
project(blockchain)

add_executable(blockchain blockchain.c)
add_executable(main query.c)

add_library(mtwister STATIC ${CMAKE_SOURCE_DIR}/libs/mtwister.c)
target_link_libraries(blockchain mtwister)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})

target_link_libraries(main ${CMAKE_SOURCE_DIR}/libs/utils.h)
target_link_libraries(blockchain ${CMAKE_SOURCE_DIR}/libs/utils.h)