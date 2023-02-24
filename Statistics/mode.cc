#include "utils.cc"
#include <iostream>
#include <Eigen/Dense>

int main(int argc, char** argv) {
  double m=0, s=0;
  int n=0, element;
  std::vector<int> elements;
  std::cin >> element;
  while (not std::cin.eof()) {
    elements.push_back(element);
    n += 1;
    std:cin >> element;
    
  }
  
  map<double,int> dicc;
  for(int i=0; i<elements.size();i++){
    int x=0;
      for(int j=0; j<elements.size();j++){
        if(elements[i]==elements[j]){
          x++;
        }
        dicc[i]=x;
      }
  }
  
  int maxvalue=0;
  double maxkey=0;

  for(const auto&pair:dicc){
    if(pair.second>maxvalue){
      maxkey= pair.first;
      maxvalue=pair.second;
    }
  }

    m=maxkey;
  
  std:cout << "Mode: " << m << std:endl;
  return 0;


}
