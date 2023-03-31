#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
using namespace std::chrono_literals;
double min_left;
double min_right;
double min_total;

void scan_callback(sensor_msgs::msg::LaserScan::SharedPtr msg)
{
    auto v = msg->ranges;
    min_left = 9999;
    for (int i=0; i<9; i++)
    {
        if (v[i]<min_left){
            min_left = v[i];
        }
    }
    std::cout << "Mínimo[0..9]: " << min_left << std::endl;
    min_right = 9999;
    for (int i=350; i<359; i++)
    {
        if (v[i]<min_right){
            min_right = v[i];
        }
    }
    std::cout << "Mínimo[350..359]: " << min_right << std::endl;
    
    
    std::cout << "··················" << std::endl;
    
    if (min_left < min_right){
        min_total=min_left;
    }
    else{
        min_total=min_right;
    }
    

}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("wandering");
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
  auto subscriber = node->create_subscription<sensor_msgs::msg::LaserScan>("/scan", 10, scan_callback);
  
  geometry_msgs::msg::Twist message;
  rclcpp::WallRate loop_rate(10ms);
  bool turn_left, turn_right;
  
  while (rclcpp::ok()) {

    if (min_total > 1) {
      turn_left = false;
      turn_right = false;
    } else if (min_left > min_right) {
      turn_left = true;
    } else {
      turn_right = true;
    }
    
    if (turn_left) {
      while (min_total < 1) {
         message.angular.z = 0.2;
         message.linear.x = 0.0;
         publisher->publish(message);
         rclcpp::spin_some(node);
        }
    } else if (turn_right) {
      while (min_total < 1) {
          message.angular.z = -0.2;
          message.linear.x = 0.0;
          publisher->publish(message);
          rclcpp::spin_some(node);
        }
    } else {
      message.angular.z = 0.0;
      message.linear.x = 0.2;
      publisher->publish(message);
      rclcpp::spin_some(node);
    }
  }
  
  rclcpp::shutdown();
  return 0;
}
  
  

