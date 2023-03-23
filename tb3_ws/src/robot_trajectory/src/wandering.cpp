#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
using namespace std::chrono_literals;

void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{




}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("wandering");
  auto subscription = node->create_subscription<sensor_msgs::msg::LaserScan>("/scan", 10, scan_callback);
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 0);

  
  rclcpp::WallRate loop_rate(10ms);

  while (rclcpp::ok()) {
    
  }
  rclcpp::shutdown();
  return 0;
}

