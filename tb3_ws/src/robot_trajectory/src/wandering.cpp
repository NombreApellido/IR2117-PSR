#include <chrono>
#include <Eigen/Dense>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
using namespace std::chrono_literals;


void scan_callback(sensor_msgs::msg::LaserScan::SharedPtr msg)
{
    auto v = msg->ranges;
    int start_index = 0, end_index = 9;
    Eigen::VectorXd segment = v.segment(start_index, end_index - start_index + 1);
    double min = segment.minCoeff();
    std::cout << "Mínimo: " << min << std::endl;
    int start_index = 350, end_index = 359;
    Eigen::VectorXd segment = v.segment(start_index, end_index - start_index + 1);
    double min = segment.minCoeff();
    std::cout << "Mínimo: " << min << std::endl;
    

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

