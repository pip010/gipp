cmake_minimum_required(VERSION 3.3)

project(gipp)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/tclap)

add_executable(crop MACOSX_BUNDLE src/pipes/crop.cpp)
target_link_libraries(crop ${ITK_LIBRARIES})
set_property(TARGET crop PROPERTY CXX_STANDARD 11)
set_property(TARGET crop PROPERTY CXX_STANDARD_REQUIRED ON)
