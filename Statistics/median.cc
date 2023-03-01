#include <iostream>
#include <Eigen/Dense>

using Eigen::VectorXd;
std::istream& operator>>(std::istream& in,
			  VectorXd& v) {
    double element;
    in>>element;
    while (not in.eof()){
        v.push_back(element);
        in >> element;
    }			  

int main() {
    VectorXd v;
    std::cin >> v;

}
