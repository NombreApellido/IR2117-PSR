#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
using namespace std::chrono_literals;
double min = 9999;

void scan_callback(sensor_msgs::msg::LaserScan::SharedPtr msg)
{
    auto v = msg->ranges;
    min = 9999;
    for (int i=0; i<9; i++)
    {
        if (v[i]<min){
            min = v[i];
        }
    }
    std::cout << "Mínimo[0..9]: " << min << std::endl;
    min = 9999;
    for (int i=350; i<359; i++)
    {
        if (v[i]<min){
            min = v[i];
        }
    }
    std::cout << "Mínimo[350..359]: " << min << std::endl;
    
    
    std::cout << "··················" << std::endl;

}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher");
  auto subscription = node->create_subscription<sensor_msgs::msg::LaserScan>("scan", 10, scan_callback);
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

  
  rclcpp::WallRate loop_rate(10ms);
  geometry_msgs::msg::Twist message;
  while (rclcpp::ok()) {
      message.linear.x = 0.2; //Velocidad lineal constante para avanzar
      if (min <= 1.0){ // Si encuentra obstáculo a 1 metro, detiene el robot
          message.linear.x = 0.0;
      }
      publisher->publish(message);
      rclcpp::spin_some(node);
      loop_rate.sleep();
  }
  rclcpp::shutdown();
  return 0;
}

