#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <math.h> 
#include <cmath>
#include <Eigen/Geometry>
using namespace std::chrono_literals;

double x_pos=0.0, y_pos=0.0, angle = 0.0, x = 0.0, y = 0.0, z = 0.0, w = 0.0, ini_angle = 0.0, distance = 0.0, angle_diff = 0.0, ini_pos = 0.0;

struct Quaternion {
    double w, x, y, z;
};

Quaternion normalize(const Quaternion& q) {
    double norm = sqrt(q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z);
    Quaternion res = { q.w/norm, q.x/norm, q.y/norm, q.z/norm };
    return res;
}

double toDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

double angleFromQuaternion(const Quaternion& q) {
    Quaternion qn = normalize(q);
    double w = qn.w, x = qn.x, y = qn.y, z = qn.z;
    double angle = 2.0 * acos(w);
    return toDegrees(angle);
}

void topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    x = msg -> pose.pose.orientation.x;
    y = msg -> pose.pose.orientation.y;
    z = msg -> pose.pose.orientation.z;
    w = msg -> pose.pose.orientation.w;
    x_pos = msg -> pose.pose.position.x;
    y_pos = msg -> pose.pose.position.y;
    if (ini_angle == 0.0 && ini_pos == 0.0) {
        Quaternion q = {x,y,z,w};
        ini_angle = angleFromQuaternion(q);
        ini_pos = sqrt(x_pos*x_pos + y_pos*y_pos);
    }
    Quaternion q = {x,y,z,w};
    angle = angleFromQuaternion(q);
    angle_diff = abs(angle - ini_angle);
    
    
    distance = sqrt(x_pos*x_pos + y_pos*y_pos);
    std::cout << "Position x: " << x << std::endl;
    std::cout << "Position y: " << y << std::endl;
    std::cout << "Angle: " << angle << std::endl;
    std::cout << "Distance: " << distance << std::endl;
    std::cout << "Angle difference: " << angle_diff << std::endl;
}


int main(int argc, char * argv[])
{
    

  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("square_odom");
  auto subscription = node->create_subscription<nav_msgs::msg::Odometry>("odom", 10, topic_callback);
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
  node->declare_parameter("linear_speed", 0.1);
  node->declare_parameter("angular_speed", 3.1416 / 20);
  node->declare_parameter("square_length", 1.0);
  geometry_msgs::msg::Twist message;
  rclcpp::WallRate loop_rate(10ms);
  
  double linear_speed = node->get_parameter("linear_speed").get_parameter_value().get<double>();
  double angular_speed = node->get_parameter("angular_speed").get_parameter_value().get<double>();
  double square_length = node->get_parameter("square_length").get_parameter_value().get<double>();
  for(int j=0; j<4; j++){
    int n= square_length;
    while (rclcpp::ok() && (distance<n)) {
      
      // move forward
      message.linear.x = linear_speed;
      publisher->publish(message);
      rclcpp::spin_some(node);
      loop_rate.sleep();
    }
    
    message.linear.x = 0.0;
    publisher->publish(message);
    
    
    n = 3.1416/2;
    while (rclcpp::ok() && ((angle_diff*3.1416)/180)<n) {
      
      // turn
      message.angular.z = angular_speed;
      publisher->publish(message);
      rclcpp::spin_some(node);
      loop_rate.sleep();
    }
    message.angular.z = 0;
    publisher->publish(message);
   }
  // send zero velocity to topic
  rclcpp::shutdown();
  return 0;
}

