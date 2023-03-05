#include "utils.hpp"

using Eigen::VectorXd;

int main() {

    VectorXd v;
    std::cin >> v;
    std::sort(std::begin(v), std::end(v));
    std::cout << "The vector is: " << std::endl;
    std::cout << v << std::endl;
}
