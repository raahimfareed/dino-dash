cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -g -Wall -I include")

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${ProjectId} ${SRC_FILES})
target_include_directories(${ProjectId} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${ProjectId} SDL2 SDL2main SDL2_image SDL2_ttf SDL2_mixer)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(${ProjectId} copy_assets)
