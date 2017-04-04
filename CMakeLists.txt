cmake_minimum_required(VERSION 3.3)

project(gipp)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/pipes")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/tclap")

SET(SRCS_LIST "" CACHE INTERNAL "SRCS_LIST")

ADD_SUBDIRECTORY(src/pipes)

message(STATUS "List of cpp(s): ${SRCS_LIST}")

add_executable(gtools MACOSX_BUNDLE "main.cpp" "src/reg_pipe.cpp" ${SRCS_LIST})
target_link_libraries(gtools ${ITK_LIBRARIES})
set_property(TARGET gtools  PROPERTY CXX_STANDARD 11)
set_property(TARGET gtools  PROPERTY CXX_STANDARD_REQUIRED ON)


add_executable(xpipe MACOSX_BUNDLE "x_main.cpp")
target_link_libraries(xpipe ${ITK_LIBRARIES})
set_property(TARGET xpipe  PROPERTY CXX_STANDARD 11)
set_property(TARGET xpipe  PROPERTY CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
