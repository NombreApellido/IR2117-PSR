#include <iostream>
#include <Eigen/Dense>

using Eigen::VectorXd;
std::istream& operator>>(std::istream& in,
			  VectorXd& v) {
    double element;
    int =0;
    in>>element;
    while (not in.eof()){
        v.resize(i+1);
        v(i++) = element;
        in >> element;
    }		
    return in;	  

int main() {
    VectorXd v;
    std::cin >> v;
    std::cout << "The vector is: " << std::endl;
    std::cout << v << std::endl;

}
