#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main() {
  bool rep = true;
  while (rep) {
    int nfilas, sumamax = 0;
    std::cout << "Introduce el número de filas de la matriz cuadrada: " << std::endl;
    std::cin >> nfilas;
    MatrixXd m(nfilas, nfilas); // Se crea la matriz deseada (?)
    for(int f=0; f<=nfilas; f++) {
      for(int c=0; c<=nfilas; c++) {
        int dato;
        std::cout << "Introduce el dato para la posición (" << f << ", " << c << ")" << std::endl;
        std::cin >> dato;
        m(f, c) = dato;
      }
    }
    if(m.isSquare()) {
      rep = false;
  }
  int sumamaxfilas=0, sumamaxcolumnas=0, sumamaxdiag1=0, sumamaxdiag2=0;
  for(int f=0; f<=nfilas; f++){
    int sum=0;
    for(int c=0; c<=nfilas; c++) {
      sum = sum + m(f, c);
    }
    if(sum > sumamaxfilas) {
      sumamaxfilas = sum;
    }
  }
  for(int f=0; f<=nfilas; f++){
    int sum=0;
    for(int c=0; c<=nfilas; c++) {
      sum = sum + m(c, f); // lo mismo que antes pero cambiando f por c
    }
    if(sum > sumamaxcolumnas) {
      sumamaxcolumnas = sum;
    }
  }
  int sumdiag1=0;
  for(int d=0; d<=nfilas; d++) {
    sumdiag1 = sumdiag1 + m(d, d);
  }
  int sumdiag2=0;
  for(int d=nfilas; d>=0; d--) {
    sumdiag2 = sumdiag2 + m(d, d);
  }
  
  std::cout << "sumamaxfilas: " << sumamaxfilas << ", sumamaxcolumnas: " << sumamaxcolumnas << ", sumamaxdiag1: " << sumamaxdiag1 << ", sumamaxdiag2: " << sumamaxdiag2 << std::endl;
  std::cout << sumamax << std::endl;


  return 0;
}
