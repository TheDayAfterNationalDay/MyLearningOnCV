cmake_minimum_required(VERSION 3.21)
project(MyLearningOnCV)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR "G:\\lib\\c++\\opencv\\mingw-build\\install\\")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(MoravecDetector paper/Ma2020/MoravecDetector.cpp)
add_executable(HarrisDetector paper/Ma2020/HarrisDetector.cpp paper/GMS/GMS.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(MoravecDetector ${OpenCV_LIBS})
target_link_libraries(HarrisDetector ${OpenCV_LIBS})
