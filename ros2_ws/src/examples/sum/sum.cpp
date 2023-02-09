#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <iostream>

int sum;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
  sum += msg->data;
  std::cout << msg->data << std::endl;
  
}

int main(int argc, char * argv[])
{
  sum = 0;
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("sum");
  auto subscription = node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
