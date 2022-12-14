cmake_minimum_required(VERSION 3.10)
project(blockchain)
set(EXECUTABLE_OUTPUT_PATH ./bin)

add_executable(blockchain ../blockchain.c)
add_executable(query ../query.c)

add_library(mtwister STATIC ../libs/mtwister.c)
target_link_libraries(blockchain mtwister)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(blockchain ${OPENSSL_LIBRARIES})

add_library(utils STATIC ../libs/utils.c)
target_link_libraries(blockchain utils)