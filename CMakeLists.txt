cmake_minimum_required(VERSION 3.1)

project(
  lineFollower
  VERSION 1.0
  LANGUAGES CXX)

find_package(OpenCV REQUIRED)

add_executable(lineFollower_image center_image.cpp)
add_executable(lineFollower_video center_video.cpp)
add_executable(lineFollower_tst lineFollower_live.cpp)

target_link_libraries(lineFollower_image ${OpenCV_LIBS})
target_link_libraries(lineFollower_video ${OpenCV_LIBS})
target_link_libraries(lineFollower_tst ${OpenCV_LIBS})