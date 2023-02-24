#include "utils.cc"
#include <iostream>
#include <Eigen/Dense>


int main(int argc, char** argv) {
  
  double m=0;
  int n=0, element;
  std::cin >> element;
  Eigen::VectorXd elements(100);
  
  while (not std::cin.eof()) {
    elements(n) = element;
    n += 1;
    std::cin >> element;
  }

  elements.conservativeResize(n);
  Eigen::Map<Eigen::VectorXd> counts(elements.size());
  
  for(int i=0; i < elements.size(); i++ ){
    counts(i) = (elements.array() == elements(i)).count();
  
  }

  int maxIndex;
  double maxCount;
  counts.maxCoeff(&maxIndex);
  maxCount = counts(maxIndex);
  m = elements(maxIndex);
  std::cout << "Mode: " << m << std::endl;
  return 0;
}
