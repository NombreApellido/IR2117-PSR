#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
using namespace std::chrono_literals;
double min = 9999;
bool obstacle_detected = false, approaching_obstacle = true;

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
      if (approaching_obstacle) { // Si se está acercando al obstáculo
          if (min > 1.0) { // Si aún no se detecta el obstáculo
              message.linear.x = 0.2; // Velocidad lineal constante para avanzar hacia adelante
              message.angular.z = 0.0;
          }
          else { // Si se detecta el obstáculo
              approaching_obstacle = false;
              obstacle_detected = true;
              message.linear.x = 0.0; // Detiene el avance
              message.angular.z = 0.2; // Velocidad angular constante para girar a la izquierda
          }
      }
      else if (obstacle_detected) { // Si se detecta el obstáculo
          if (min <= 1.0) { // Si todavía detecta el obstáculo
              message.linear.x = 0.0; // Detiene el avance
              message.angular.z = 0.2; // Velocidad angular constante para girar a la izquierda
          }
          else { // Si ya no detecta el obstáculo
              obstacle_detected = false;
              approaching_obstacle = true;
              message.linear.x = 0.2; // Velocidad lineal constante para avanzar hacia adelante
              message.angular.z = 0.0;
          }
      }
      publisher->publish(message);
      rclcpp::spin_some(node);
      loop_rate.sleep();
      }
  rclcpp::shutdown();
  return 0;
}

