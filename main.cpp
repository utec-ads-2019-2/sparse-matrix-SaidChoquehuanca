#include <iostream>

#include "tester/tester.h"

int main() {

    /*Matrix<int> matriz(4,5);

    matriz.set(0,2,3);
    matriz.set(0,4,4);
    matriz.set(1,1,5);
    matriz.set(1,3,7);
    matriz.set(3,1,2);
    matriz.set(3,2,6);

    Matrix<int>matriz_two(5,4);
    matriz_two.set(0,1,4);
    matriz_two.set(0,0,3);
    matriz_two.set(1,3,1);
    matriz_two.set(1,4,2);
    matriz_two.set(2,2,5);
    matriz_two.set(2,3,6);
    matriz_two.set(4,2,4);
    matriz_two.set(3,1,7);

    Matrix<int> matriz_mul = matriz * matriz_two;
    Matrix<int> matriz_sum = matriz + matriz_two;
    Matrix<int> matriz_res = matriz - matriz_two;
    Matrix<int> matriz_trans = matriz.transpose();
    Matrix<int> matriz_mul_escalar = matriz*4;

    matriz_mul.print();
    matriz_sum.print();
    matriz_res.print();
    matriz_trans.print();
    matriz_mul_escalar.print();*/

    Tester::execute();
    return EXIT_SUCCESS;
}

