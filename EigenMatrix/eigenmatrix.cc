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
  cout << sumamax << std::endl;


  return 0;
}
