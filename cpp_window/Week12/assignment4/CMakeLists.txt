cmake_minimum_required(VERSION 3.4.1)

project(demo)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRC)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(demo ${DIR_SRC})

target_link_libraries(demo libopenblas.lib)

