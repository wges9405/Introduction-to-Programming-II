#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdio.h>
using namespace std;

class Matrix
{

public:
    Matrix();
    Matrix (const int , const int [50][50]);
    Matrix add(const Matrix) const;//add function
    Matrix subtract(const Matrix) const;//subtract function
    Matrix multiplication(const Matrix) const;//multiply function
    Matrix inc() const;//increased by 1
    void Transpose() const;//Transpose function
    void output() const;//Note that each output should be followed by a new
                        //line character.
private:
    int matrix[50][50];
    int matrix_size;
}; //end class Matrix

//////////////////////////////////////////////////////////////////////////////

Matrix::Matrix() {
    int m, n;
    this->matrix_size=0;
    for (m=0; m<50;m++)
        for (n=0;n<50;n++)
            this->matrix[m][n]=0;
}
Matrix::Matrix(const int N, const int temp[50][50]) {
    int m, n;
    this->matrix_size=N;
    for (m=0;m<N;m++)
        for (n=0;n<N;n++)
            this->matrix[m][n] = temp[m][n];
}

Matrix Matrix::add(const Matrix b) const {
    Matrix temp;
    temp.matrix_size = b.matrix_size;
    for (int m = 0 ; m < temp.matrix_size ; m++)
        for (int n = 0 ; n < temp.matrix_size ; n++)
            temp.matrix[m][n] += this->matrix[m][n] + b.matrix[m][n];
    return temp;
}

Matrix Matrix::subtract(const Matrix b) const {
    Matrix temp;
    temp.matrix_size = b.matrix_size;
    for (int m = 0 ; m < temp.matrix_size ; m++)
        for (int n = 0 ; n < temp.matrix_size ; n++)
            temp.matrix[m][n] += this->matrix[m][n] - b.matrix[m][n];
    return temp;
}

Matrix Matrix::multiplication(const Matrix b) const {
    Matrix temp;
    temp.matrix_size = b.matrix_size;
    for (int m = 0 ; m < temp.matrix_size ; m++)
        for (int n = 0 ; n < temp.matrix_size ; n++)
            for (int k = 0 ; k < temp.matrix_size ; k++)
            temp.matrix[m][n] += this->matrix[m][k] * b.matrix[k][n];
    return temp;
}

Matrix Matrix::inc() const {
    Matrix temp;
    temp.matrix_size = this->matrix_size;
    for (int m = 0 ; m < temp.matrix_size ; m++)
        for (int n = 0 ; n < temp.matrix_size ; n++)
            temp.matrix[m][n] = (this->matrix[m][n] + 1 ) % 10;
    return temp;
}

void Matrix::Transpose() const {
    for (int m=0;m<this->matrix_size;m++) {
        for (int n=0;n<this->matrix_size;n++) {
            if (n) cout << " " << this->matrix[n][m];
            else cout << this->matrix[n][m];
        }
        cout << endl;
    }
}

void Matrix::output() const {
    for (int m=0;m<this->matrix_size;m++) {
        for (int n=0;n<this->matrix_size;n++) {
            if (n) cout << " " << this->matrix[m][n];
            else cout << this->matrix[m][n];
        }
        cout << endl;
    }
}

/*
I:
3
1 2 3
1 1 1
1 1 2
1 1 1
1 1 1
1 1 1

O:
2 3 4
2 2 2
2 2 3

0 1 2
0 0 0
0 0 1

6 6 6
3 3 3
4 4 4

2 3 4
2 2 2
2 2 3

2 2 2
2 2 2
2 2 2

1 1 1
2 1 1
3 1 2

1 1 1
1 1 1
1 1 1
*/


#endif /* function_h */
