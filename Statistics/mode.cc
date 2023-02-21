#include <iostream>
#include <vector>
#include <map>
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
  int x=0;
  for(int j=0; j<elements.size();j++){
    if(elements[i]==elements[j]){
      x++;
    }
    dicc[i]=x;
  }
  
  std:cout << "Mode: " << m << std:endl;
  return 0;


}
