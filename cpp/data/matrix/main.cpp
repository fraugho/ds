#include <iostream>
#include "matrix.hpp"

Matrix<int>* ddd_to_dd(Matrix<int>* a);
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

    Matrix<int> C = A * B;
    C.print_matrix();

    int d_rows = 3, d_cols = 3;
    Matrix<int> D(d_rows,d_cols);
    for (int i = 0; i < d_rows; ++i){
        for (int j = 0; j < d_cols; ++j){
            D.data[i][j] = j + 1;
        }
    }
    D *= 2;

    Matrix<int>* E = matrix_mul(&D, &D);
    std::cout << "D matrix\n";
    E->print_matrix();
    delete E;

    Matrix<int> F(3, 1);
    F.data[0][0] = 1;
    F.data[1][0] = 1;
    F.data[2][0] = 1;
    std::cout << "F\n";
    F.print_matrix();
    Matrix<int>* G = ddd_to_dd(&F);
    G->print_matrix();
    return 0;
}

Matrix<int>* ddd_to_dd(Matrix<int>* a){
    Matrix<int> b(2, 3);
    b.data[0][0] = 1;
    b.data[1][2] = 1;
    std::cout << "B\n";
    b.print_matrix();

    return matrix_mul(&b, a);
}
