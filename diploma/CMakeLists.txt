cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(diploma)

set(Torch_DIR /Users/jhilario/Developer/libtorch/share/cmake/Torch)
find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(diploma main.cpp models/BaselineStdMNIST.cpp models/BaselineStdMNIST.h Agent.cpp Agent.h Config.cpp Config.h utils.cpp utils.h Dataset.cpp Dataset.h)
target_link_libraries(diploma "${TORCH_LIBRARIES}")
set_property(TARGET diploma PROPERTY CXX_STANDARD 14)

