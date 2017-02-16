cmake_minimum_required(VERSION 2.8)
project( imsusan )
find_package(OpenCV REQUIRED )
find_package(Boost 1.55.0 COMPONENTS filesystem system REQUIRED)
set(ROOT ~)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

add_compile_options(-std=c++11)
add_compile_options(-DLIB)

set(imsusan_SOURCES	main_susan.cpp susan.cpp susan2l.c )
link_directories (${ROOT}/usr/local/lib)
include_directories(.)
include_directories(${ROOT}/usr/local/include)
include_directories(${ROOT}/usr/local/include/cv2x)
include_directories(${OPENCV_INCLUDE_DIRS})	

add_executable( imsusan ${imsusan_SOURCES} )
target_link_libraries( imsusan ${OpenCV_LIBS} ${Boost_LIBRARIES}  cvm )
install(TARGETS imsusan RUNTIME DESTINATION bin)	


