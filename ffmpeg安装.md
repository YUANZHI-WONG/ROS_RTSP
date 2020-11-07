## ffmpeg
## 支持库的安装

```
sudo apt-get install -y autoconf automake build-essential git libass-dev libfreetype6-dev libsdl2-dev libtheora-dev libtool libva-dev libvdpau-dev libvorbis-dev libxcb1-dev libxcb-shm0-dev libxcb-xfixes0-dev pkg-config texinfo wget zlib1g-dev yasm libsdl2-dev libx264-dev libx265-dev libfdk-aac-dev
```

```
sudo apt install libavformat-dev libavcodec-dev libswresample-dev libswscale-dev libavutil-dev  libsdl1.2-dev

```
支持库的简介如下：    

 - libavutil是一个包含简化编程功能的库，包括随机数生成器、数据结构、数学例程、核心多媒体实用程序等。  
 - libavcodec是一个包含音频/视频 解码器和编码器的库。  
 - libavformat是一个库，包含用于多媒体容器格式的合成和拆分的库。  
 - libavdevice是一个包含输入和输出设备的库，用于从许多常见的多媒体输入/输出软件框架(包括Video4Linux, Video4Linux2, VfW, and ALSA）中获取和呈现多媒体输入/输出软件框架。  
 - libavfilter是一个包含媒体过滤器的库。  
 - libswscale是一个执行高度优化的图像缩放和颜色空间/像素格式转换操作的库。  
 - libswressample是一个执行高度优化的音频重采样、重矩阵和示例格式转换操作的库。

## 安装

下载ffmpeg源码包

```
git clone git://source.ffmpeg.org/ffmpeg.git ffmpeg
```

```
./configure   --enable-shared  --prefix=/usr/include/ffmpeg  --enable-gpl --enable-libx264  --enable-libx265   

```

若首次configure 会提示yasm未安装错误，处理这个问题很简单，直接安装yasm即可，具体方法是 在命令行终端执行sudo apt-get install yasm。

```
make
make install
```

增加安装目录的动态链接库:
```
export LD_LIBRARY_PATH=/usr/include/ffmpeg/lib:$LD_LIBRARY_PATH
PATH=/usr/include/ffmpeg/bin:$PATH
```

查看指令依赖的动态库

```
ldd ffmpeg 
```

## 测试
```
ffmpeg  –version
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/2019053020381038.png)

播放IPC摄像头的RTSP流媒体：

```
ffplay rtsp://192.168.0.123/live/av0
```

cmake
```
cmake_minimum_required(VERSION 2.8)

PROJECT(testFFMpeg)
SET(SRC_LIST main.cpp
#加入ffmpeg的头文件所在目录，可以根据具体安装目录修改
include_directories("/usr/include/ffmpeg")

ADD_EXECUTABLE(testFFMpegDemo ${SRC_LIST})

target_link_libraries(testFFMpegDemo libavutil.so libavcodec.so libavformat.so libavdevice.so libavfilter.so libswscale.so libpostproc.so )

```
