#cmake_minimum_required(VERSION 2.8)
cmake_minimum_required(VERSION 3.5)
project(serial_communication)
message("start make serial_communication")

# 一定要加-march=native， 不然使用pcl的一些函数会报错
#add_definitions(-DCPP11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -march=native")

set(ALL_TARGET_LIBRARIES "")
include(cmake/boost.cmake)
include(cmake/catkin.cmake)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${catkin_INCLUDE_DIRS}
)

file(GLOB_RECURSE ALL_SRCS "src/*.cpp")
#file(GLOB_RECURSE THIRD_PARTY_SRCS "Thirdparty/*.cpp")
#list(REMOVE_ITEM ALL_SRCS ${THIRD_PARTY_SRCS})


add_executable(serial_communication_node node/serial_communication_node.cpp ${ALL_SRCS})
target_link_libraries(serial_communication_node ${ALL_TARGET_LIBRARIES})
