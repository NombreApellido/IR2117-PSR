#include "utils.hpp"

using Eigen::VectorXd;

int main() {

    VectorXd v;
    std::cin >> v;
    std::sort(v.data(), v.data()+v.size());
    std::cout << "The vector is: " << std::endl;
    std::cout << v << std::endl;
}
