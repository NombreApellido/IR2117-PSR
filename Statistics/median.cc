#include "utils.cc"

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
  if(n%2!=0) {
      m = elements[n/2]; 
  }
  else{
    m=(elements[n/2]+elements[n/2+1])/2;
  }
  cout<<"Number of elements: "<<n<<endl;
  for(int i=0; i<sizeof(elements)-1; i++){
    for (int j=0; j<n-i-1;j++){
      if(elements[j]>elements[j+1]){
        swap(elements[j], elements[j+1]);
      }
    }
  }
  cout<<"Sorted elements are: ";
  for(int i=0; x<elements.size(); i++) {
    cout << elements[i];
  }
  std:cout << "Median: " << m << std:endl;
  return 0;
  

}
