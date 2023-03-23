#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
using namespace std::chrono_literals;

void scan_callback(sensor_msgs::msg::LaserScan::SharedPtr msg)
{

    for (int i=0; i<9; i++)
    {
        std::cout << msg->ranges[i] << std::endl;
    }
    for (int i=350; i<359; i++)
    {
        std::cout << msg->ranges[i] << std::endl;
    }
    

}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher");
  auto subscription = node->create_subscription<sensor_msgs::msg::LaserScan>("scan", 10, scan_callback);
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

  
  rclcpp::WallRate loop_rate(10ms);
  geometry_msgs::msg::Twist message;
  while (rclcpp::ok()) {
      message.linear.x = 0.0;
      publisher->publish(message);
      rclcpp::spin_some(node);
      loop_rate.sleep();
  }
  rclcpp::shutdown();
  return 0;
}

