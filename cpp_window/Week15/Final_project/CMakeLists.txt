cmake_minimum_required(VERSION 3.17)
project(Final_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH   C:\\OpenCv_finalProject)
set(OpenCV_DIR C:\\OpenCv_finalProject\\x64\\vc15\\lib)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Final_project main.cpp PoolLayer.h ReLuLayer.h FullConnectLayer.h Layer.h Control.h MyException.cpp MyException.h)

target_link_libraries(Final_project ${OpenCV_LIBS})

