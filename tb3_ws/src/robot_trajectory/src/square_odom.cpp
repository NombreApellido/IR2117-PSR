#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <math.h> 
#include <Eigen/Geometry>

double x_pos=0.0, y_pos=0.0, angle = 0.0, x = 0.0, y = 0.0, z = 0.0, w = 0.0, ini_angle = 0.0, distance = 0.0, angle_diff = 0.0;
Eigen::Vector3d ini_pos(0.0, 0.0, 0.0);
Eigen::Vector3d posicion_actual(0.0, 0.0, 0.0);
using namespace std::chrono_literals;

Eigen::Vector3d calcularPosicion(const Eigen::Quaterniond& q) {
    Eigen::Vector3d pos(0.0, 0.0, 0.0);
    Eigen::Vector3d d(1.0, 0.0, 0.0);

    pos += d * 2 * (q.x()*q.z() + q.w()*q.y());
    d = Eigen::Vector3d(0.0, 1.0, 0.0);
    pos += d * 2 * (q.y()*q.z() - q.w()*q.x());
    d = Eigen::Vector3d(0.0, 0.0, 1.0);
    pos += d * (1 - 2*q.x()*q.x() - 2*q.y()*q.y());

    return pos;
}

double angulo(const Eigen::Quaterniond& q)
{
    return atan2(2*(q.w()*q.z()+q.x()*q.y()), 1-2*(q.y()*q.y()+q.z()*q.z()));
}


double anguloActual(const Eigen::Quaterniond& q, double anguloInicial)
{
    Eigen::Quaterniond q0(1, 0, 0, 0); // Cuaternión que representa la rotación inicial (sin rotación).
    Eigen::Quaterniond qr = q * q0.inverse(); // Cuaternión que representa la rotación actual.
    Eigen::AngleAxisd aa(qr); // Conversión del cuaternión a un eje y ángulo de rotación.
    return aa.angle() - anguloInicial; // Ángulo de rotación actual, ajustado por el ángulo inicial.
}

void topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    x = msg -> pose.pose.orientation.x;
    y = msg -> pose.pose.orientation.y;
    z = msg -> pose.pose.orientation.z;
    w = msg -> pose.pose.orientation.w;
    Eigen::Quaterniond q(w, x, y, z);
    
    
    if (ini_pos.isApprox(Eigen::Vector3d::Zero(), 1e-6) && ini_angle == 0) {
        Eigen::Vector3d ini0 = calcularPosicion(q);
        ini_pos = ini0.transpose();
        ini_angle = angulo(q);
    }
    
    angle = angulo(q);
    angle_diff = angle - ini_angle;
    x_pos = msg -> pose.pose.position.x;
    y_pos = msg -> pose.pose.position.y;
    
    
    Eigen::Vector3d pos = calcularPosicion(q);
    posicion_actual = pos.transpose();
    distance = (posicion_actual - ini_pos).norm();
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
    int n= square_length / (0.01 * linear_speed);
    while (rclcpp::ok() && (distance<n)) {
      
      // move forward
      message.linear.x = linear_speed;
      publisher->publish(message);
      rclcpp::spin_some(node);
      loop_rate.sleep();
    }
    
    message.linear.x = 0.0;
    publisher->publish(message);
    
    
    n = (3.1416 / 2) / (0.01 * angular_speed);
    while (rclcpp::ok() && (((angle_diff*3.1416)/180)<n)) {
      
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

