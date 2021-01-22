cmake_minimum_required (VERSION 3.0)
project(TWSclient)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


SET(COMPILE_DEFINITIONS -pthread -Wall -Wno-switch -Wpedantic)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

FIND_PACKAGE( Boost 1.71 COMPONENTS REQUIRED thread)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_subdirectory(lib)

include_directories(
    "${PROJECT_SOURCE_DIR}/lib/client"
    "${PROJECT_SOURCE_DIR}/src"
)

# add the executable
FILE(GLOB SRC_FILES src/*.cpp)
add_executable(test ${SRC_FILES})

target_link_libraries(test PUBLIC tws_api Threads::Threads Boost::thread)
