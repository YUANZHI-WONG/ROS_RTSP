#ifndef __FFMPEG_DECODE_H__
#define __FFMPEG_DECODE_H__
 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
//图像转换结构需要引入的头文件
#include "libswscale/swscale.h"
};
 
 
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib  ")
#pragma comment(lib, "avutil.lib    ")
#pragma comment(lib, "avdevice.lib  ")
#pragma comment(lib, "avfilter.lib  ")
#pragma comment(lib, "postproc.lib  ")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib   ")
 
using namespace std;

class ffmpegDecode
{
public:
    ffmpegDecode(char * file = NULL);
    ~ffmpegDecode();
 
    cv::Mat getDecodedFrame();
    
    int readOneFrame();
    
 
private:
    AVFrame    *pAvFrame;
    AVFormatContext    *pFormatCtx;
    AVCodecContext    *pCodecCtx;
    AVCodec            *pCodec;
 
    int    i; 
    int videoindex;
 
    std::string filepath;
    int ret, got_picture;
    SwsContext *img_convert_ctx;
    int y_size;
    AVPacket *packet;
 
    cv::Mat *pCvMat;
 
    void init();
    void openDecode();
    void prepare();
    void get(AVCodecContext *pCodecCtx, SwsContext *img_convert_ctx,AVFrame    *pFrame);
};
 
#endif
