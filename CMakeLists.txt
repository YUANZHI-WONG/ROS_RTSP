# cmake 最低版本号要求
cmake_minimum_required(VERSION 2.8)
 
#设置project name
project(camera_driver)
 
#设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
 
# aux_source_directory会查找指定目录下的所有源文件，并将结果存入指定变量名
# 这里是将当前目录下的所有源文件存进变量SRC_LIST
#aux_source_directory(./src SRC_LIST)
SET(SRC_LIST ./src/camera_timer.cpp ./src/ffmpegDecode.cpp ./src/ffmpegDecode.h)
# 设置ffmpeg依赖库及头文件所在目录，并存进指定变量


#set(ffmpeg_libs_DIR /usr/local/ffmpeg/lib)
set(ffmpeg_DIR "/usr/local/ffmpeg")

set(OpenCV_DIR /usr/local/opencv4)


#用find_package引入外部依赖包
find_package(       
      catkin REQUIRED
      COMPONENTS
      roscpp
      message_generation
      sensor_msgs
      
      cv_bridge
      image_transport
      camera_info_manager
      tf      
      )
find_package( OpenCV REQUIRED )



catkin_package(
    CATKIN_DEPENDS
      roscpp
      message_runtime
      sensor_msgs
      
      cv_bridge
      image_transport
      camera_info_manager
      tf)
 


# 添加头文件路径到编译器的头文件搜索路径下，多个路径以空格分隔
include_directories( ${OpenCV_INCLUDE_DIRS} ${ffmpeg_headers_DIR}  ${catkin_INCLUDE_DIRS})
#对于find_package找不到的外部依赖库，可以用add_library添加
# SHARED表示添加的是动态库
# IMPORTED表示是引入已经存在的动态库
add_library( ffmpegDecode ./src/ffmpegDecode.cpp )

#指定所添加依赖库的导入路径

#add_library( avcodec SHARED IMPORTED )
#set_target_properties( avcodec PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libavcodec.so )
 
#add_library( avfilter SHARED IMPORTED )
#set_target_properties( avfilter PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libavfilter.so )
 


#add_library( swscale SHARED IMPORTED )
#set_target_properties( swscale PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libswscale.so )
 
#add_library( avformat SHARED IMPORTED )
#set_target_properties( avformat PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libavformat.so )
 
#add_library( avutil SHARED IMPORTED )
#set_target_properties( avutil PROPERTIES IMPORTED_LOCATION ${ffmpeg_libs_DIR}/libavutil.so )
 
 

 
 
# 添加一个可执行目标，名称可自己指定，本例是直接用工程名称命名的
# 该可执行目标是由SRC_LIST中所列出的源文件生成
add_executable(${PROJECT_NAME} ${SRC_LIST} )
# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS} )

#link_directories( ${ffmpeg_libs_DIR} )
 
# 链接目标文件与依赖库
#target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ${catkin_LIBRARIES} avcodec avformat avutil swscale swscale avfilter ffmpegDecode )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ${catkin_LIBRARIES} libavcodec.so libavformat.so libavutil.so libswscale.so libavfilter.so libswresample.so libpostproc.so ffmpegDecode )



install(TARGETS camera_driver
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
