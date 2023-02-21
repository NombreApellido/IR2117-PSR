#include "utils.hpp"
#include <iostream>
#include <vector>
#include <map>

std::vector<int> ReadElements() {
  int element;
  std::vector<int> elements;
  std::cin >> element;
  while (not std::cin.eof()) {
    elements.push_back(element);
    std::cin >> element;
    
  }
  return elements;	

}
