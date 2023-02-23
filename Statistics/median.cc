#include "utils.cc"
#include <iostream>
#include <Eigen/Dense>

int main(int argc, char** argv) {
  double median=0, s=0;
  int n=0, element;
  Eigen::VectorXd elements(100);
  std::cin >> element;
  while (not std::cin.eof()) {
    elements(n) = element;
    n += 1;
    std:cin >> element;
    
  }
  elements.conservativeResize(n); // ajustamos el tamaño del vector
  std::sort(elements.data(), elements.data()+n);
  
  if(n%2!=0) {
      m = elements(n/2); 
  }
  else{
    m=(elements(n/2)+elements(n/2+1))/2;
  }
  cout<<"Number of elements: " << n << endl;
  cout<<"Sorted elements are: " << elements << std::endl;
  for(int i=0; x<elements.size(); i++) {
    cout << elements[i];
  }
  std:cout << "Median: " << m << std:endl;
  return 0;
  

}
