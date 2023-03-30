#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>

using namespace std::chrono_literals;

void callback_front(const example_interfaces::msg::Bool::SharedPtr msg)
{

}

void callback_left(const example_interfaces::msg::Bool::SharedPtr msg)
{

}

void callback_right(const example_interfaces::msg::Bool::SharedPtr msg)
{

}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("avoidance");
  auto publisher = node->create_publisher<geometry::msg::Twist>("cmd_vel", 10);
  auto subscription = node->create_subscription<geometry::msg::Twist>("/front/obstacle", 10, callback_front);
  auto subscription = node->create_subscription<geometry::msg::Twist>("/left/obstacle", 10, callback_left);
  auto subscription = node->create_subscription<geometry::msg::Twist>("/right/obstacle", 10, callback_right);
  geometry_msgs::msg::Twist message;
  rclcpp::WallRate loop_rate(50ms);
  
  while (rclcpp::ok()) {
      publisher->publish(message);
      rclcpp::spin_some(node);
      loop_rate.sleep();
  }
  rclcpp::shutdown();
  return 0;
}

