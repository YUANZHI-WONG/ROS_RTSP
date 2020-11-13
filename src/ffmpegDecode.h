#ifndef __FFMPEG_DECODE_H__
#define __FFMPEG_DECODE_H__
 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

extern "C"   /*这里必须要使用C方式导入*/
{
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"
#include "libavutil/avutil.h"
#include "libavutil/time.h"
#include "libswscale/swscale.h"
#include "libavutil/pixdesc.h"
}
 
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "postproc.lib")
 
using namespace std;
using namespace cv;
 
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
    
    char *filepath;
    int ret, got_picture;
    SwsContext *img_convert_ctx;
    int y_size;
    AVPacket *packet;

    AVDictionary *optionsDict;
 
    cv::Mat *pCvMat;
    
 
    void init();
    void openDecode();
    
    void get(AVCodecContext *pCodecCtx, SwsContext *img_convert_ctx,AVFrame    *pFrame);
    AVPixelFormat ConvertDeprecatedFormat(enum AVPixelFormat format);
};
 
#endif
