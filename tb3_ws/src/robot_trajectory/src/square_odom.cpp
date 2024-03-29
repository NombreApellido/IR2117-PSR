#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <math.h> 
#include <cmath>
#include <Eigen/Geometry>
using namespace std::chrono_literals;

double x_pos=0.0, y_pos=0.0, angle = 0.0, x = 0.0, y = 0.0, z = 0.0, w = 0.0, ini_angle = 0.0, distance = 0.0, ini_posx = 0.0, ini_posy = 0.0, sin1=0.0, cos1=0.0;


void topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    if (ini_angle == 0.0 && ini_posx == 0.0 && ini_posy == 0.0) {
         x = msg -> pose.pose.orientation.x;
         y = msg -> pose.pose.orientation.y;
         z = msg -> pose.pose.orientation.z;
         w = msg -> pose.pose.orientation.w;
         sin1 = 2* (w*z + x*y);
         cos1 = 1 - 2*(y*y + z*z);
         ini_angle = atan2(sin1, cos1);
         ini_posx = x;
         ini_posy = y;
    }
    x = msg -> pose.pose.orientation.x;
    y = msg -> pose.pose.orientation.y;
    z = msg -> pose.pose.orientation.z;
    w = msg -> pose.pose.orientation.w;
    x_pos = msg -> pose.pose.position.x;
    y_pos = msg -> pose.pose.position.y;
    sin1 = 2* (w*z + x*y);
    cos1 = 1 - 2*(y*y + z*z);
    angle = atan2(sin1, cos1);
    if (angle < 0) {
    	angle += 2 * M_PI;
    }
    
    
    distance = std::sqrt(std::pow(x_pos - ini_posx, 2) + std::pow(y_pos - ini_posy, 2));
    std::cout << "Position x: " << x << std::endl;
    std::cout << "Position y: " << y << std::endl;
    std::cout << "Angle: " << angle << std::endl;
    std::cout << "Distance: " << distance << std::endl;
    std::cout << "··················" << std::endl;
}


int main(int argc, char * argv[])
{
    

  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("subscriber");
  auto subscription = node->create_subscription<nav_msgs::msg::Odometry>("odom", 10, topic_callback);
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  node->declare_parameter("linear_speed", 0.1);
  node->declare_parameter("angular_speed", 3.1416 / 20);
  node->declare_parameter("square_length", 1.0);
  geometry_msgs::msg::Twist message;
  rclcpp::WallRate loop_rate(10ms);
  
  double linear_speed = node->get_parameter("linear_speed").get_parameter_value().get<double>();
  double angular_speed = node->get_parameter("angular_speed").get_parameter_value().get<double>();
  double square_length = node->get_parameter("square_length").get_parameter_value().get<double>();
  
  const nav_msgs::msg::Odometry::SharedPtr msg;
  for(int j=1; j<=4; j++)
  {
      while (rclcpp::ok() && (distance<square_length)) {
      
          // move forward
          message.linear.x = linear_speed;
          publisher->publish(message);
          rclcpp::spin_some(node);
          loop_rate.sleep();
        }
    
        message.linear.x = 0;
        publisher->publish(message);
        rclcpp::spin_some(node);
        loop_rate.sleep();
        ini_posx = x_pos;
        ini_posy = y_pos;
        loop_rate.sleep();
        
        double target_angle = (3.1416/2)+ini_angle;
        if (target_angle > 2*3.1416) { 
      	target_angle = 6.28;
  	
        }
        while (rclcpp::ok() && (angle<target_angle)) 
        {
            // turn
            message.linear.x = 0;
            if ( (target_angle - angle) > 0.25 ) 
            {
   	         message.angular.z = angular_speed;
            } 
            else 
            {
                message.angular.z = 0.1;
            }
            publisher->publish(message);
            rclcpp::spin_some(node);
            loop_rate.sleep();
        }
        message.angular.z = 0;
        publisher->publish(message);
        ini_angle=angle;
        loop_rate.sleep();
   }
  // send zero velocity to topic
  rclcpp::shutdown();
  return 0;
}

