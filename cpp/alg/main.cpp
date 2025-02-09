#include <iostream>
#include "matrix.hpp"

int main(){
    int a_rows = 1, a_cols = 3;
    int b_rows = 3, b_cols = 2;

    Matrix<int> A(a_rows,a_cols);
    for (int i = 0; i < a_rows; ++i){
        for (int j = 0; j < a_cols; ++j){
            A.data[i][j] = j + 1;
        }
    }

    Matrix<int> B(b_rows,b_cols);
    for (int i = 0; i < b_rows; ++i){
        for (int j = 0; j < b_cols; ++j){
            B.data[i][j] = j + 1;
        }
    }

    Matrix<int>* C = matrix_mul<int>(&A, &B);
    std::cout << "C matrix\n";
    C->print_matrix();
    delete C;


    int d_rows = 3, d_cols = 3;
    Matrix<int> D(d_rows,d_cols);
    for (int i = 0; i < d_rows; ++i){
        for (int j = 0; j < d_cols; ++j){
            D.data[i][j] = j + 1;
        }
    }

    Matrix<int>* E = matrix_mul(&D, &D);
    std::cout << "D matrix\n";
    E->print_matrix();
    delete E;
}
