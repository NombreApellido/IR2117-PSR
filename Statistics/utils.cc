#include "utils.hpp"
#include <map>

using Eigen::VectorXd;

int main() {

    VectorXd v;
    std::cin >> v;
    std::sort(v.data(), v.data()+v.size());
    std::cout << "The vector is: " << std::endl;
    std::cout << v << std::endl;
    int middle = v.size()/2;
    double m;
    if (v.size()%2==0){
        m = (v[middle]+v[middle-1]/2;
    }
    else{
        m = v[middle];
    }
    std::cout << "Median: " << m << std::endl;
}
