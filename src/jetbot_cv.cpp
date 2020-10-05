#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


static const std::string OPENCV_WINDOW = "Image";

using namespace cv;

class Object_Detection
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  
public:
  Object_Detection()
    : it_(nh_)
  {
    // Subscribe to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/jetbot_camera/image_raw", 1, &Object_Detection::imageCb, this);
    image_pub_ = it_.advertise("/jetbot_cv/raw_image", 1);
    cv::namedWindow(OPENCV_WINDOW);
  }

  ~Object_Detection()
  {
    destroyWindow(OPENCV_WINDOW);
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {

    cv_bridge::CvImagePtr cv_ptr;
    namespace enc = sensor_msgs::image_encodings;

    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    object_detection(cv_ptr->image);
    image_pub_.publish(cv_ptr->toImageMsg());
    
  }
  
  
  void object_detection(cv::Mat src)
  {
       imshow(OPENCV_WINDOW, src);
       double size_factor = 0.5;
       resize(src, src, Size(), size_factor, size_factor, INTER_LINEAR);
       imshow(OPENCV_WINDOW, src);
       waitKey(3);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Object_Detection");
  Object_Detection od;
  ros::spin();
  return 0;
}
