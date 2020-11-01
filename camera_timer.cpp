
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>

#include "ffmpegDecode.h"

class CameraDriver
{
public:
  enum Default
  {
    DEFAULT_FPS = 10
  };

  CameraDriver( std::string  camera_url ): nh( "~" ) , it( nh ) , rtsp_read( camera_url )
  {
    
    if ( not rtsp_read.readOneFrame(); )
    {
      ROS_ERROR_STREAM( "Failed to open camera device!" );
      ros::shutdown();
      return;
    }

    nh.param<int>( "fps", fps, DEFAULT_FPS );
    ros::Duration period = ros::Duration( 1. / fps );

    pub_image_raw = it.advertise( "image_raw", 1 );

    frame = boost::make_shared< cv_bridge::CvImage >();
    frame->encoding = sensor_msgs::image_encodings::BGR8;

    timer = nh.createTimer( period, &CameraDriver::capture, this );
  }

  ~CameraDriver()
  {
    camera.release();
  }

  void capture( const ros::TimerEvent& te )
  {
    //camera >> frame->image;
    rtsp_read.readOneFrame();
    rtsp_read.getDecodedFrame() >> frame->image;


    if( not frame->image.empty() )
    {
      frame->header.stamp = ros::Time::now();
      pub_image_raw.publish( frame->toImageMsg() );
    }
  }

private:
  ros::NodeHandle nh;
  image_transport::ImageTransport it;
  image_transport::Publisher pub_image_raw;

  int camera_index;
  int fps;

  //cv::VideoCapture camera;

  ffmpegDecode rtsp_read

  cv::Mat image;

  cv_bridge::CvImagePtr frame;

  ros::Timer timer;
};


int main( int argc, char* argv[] )
{
  ros::init( argc, argv, "camera" );

  ros::NodeHandle nh( "~" );

  //int camera_index = CameraDriver::DEFAULT_CAMERA_INDEX;
  //nh.param( "camera_index", camera_index, camera_index );

  std::string camera_rtsp; 
  
  nh.param<std::string>("camera_rtsp_url",camera_rtsp,"rtmp://58.200.131.2:1935/livetv/hunantv");

  CameraDriver camera_driver( camera_rtsp );

  while( ros::ok() )
  {
    ros::spin();
  }

  return EXIT_SUCCESS;
}

