cmake_minimum_required(VERSION 3.3)

project(gipp)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/tclap)

macro(gen_target arg1)
  add_executable(${arg1} MACOSX_BUNDLE "src/pipes/${arg1}.cpp")
  target_link_libraries(${arg1} ${ITK_LIBRARIES})
  set_property(TARGET ${arg1}  PROPERTY CXX_STANDARD 11)
  set_property(TARGET ${arg1}  PROPERTY CXX_STANDARD_REQUIRED ON)
endmacro(gen_target)


gen_target(crop)

gen_target(threshold)

gen_target(dilate)

#gen_target(ops)

#gen_target(testpipe)
