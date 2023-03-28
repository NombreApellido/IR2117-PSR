#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/laser_scan.hpp"
#include <iostream>

void callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{

}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("detector");
  auto subscription = node->create_subscription<std_msgs::msg::String>("scan", 10, callback);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

