#include <iostream>
using namespace std;

class Matrix {
 private:
  int size_row, size_col;
  int **arr;

 public:
  Matrix(int row, int col) {
    size_row = row;
    size_col = col;
    arr = new int *[row];
    for (int i = 0; i < row; i++) {
      arr[i] = new int[col];
    }
    init_Matrix();
  };
  void init_Matrix() {
    for (int i = 0; i < size_row; i++) {
      for (int j = 0; j < size_col; j++) {
        if (i == j)
          arr[i][j] = 1;
        else
          arr[i][j] = 0;
      }
    }
  }
  int *get_col(int col_id) const {
    int *tmparr = new int[size_row];
    for (int i = 0; i < size_row; i++) {
      tmparr[i] = arr[i][col_id];
    }
    return tmparr;
  }
  int *get_row(int row_id) const {
    int *tmparr = new int[size_col];
    for (int i = 0; i < size_col; i++) {
      tmparr[i] = arr[row_id][i];
    }
    return tmparr;
  }
  int get_value(int i, int j) const { return arr[i][j]; }
  void set_value(int i, int j, int val) { arr[i][j] = val; }
  const int get_size_row() const { return size_row; }
  const int get_size_col() const { return size_col; }
  Matrix operator*(const Matrix &a) const;  //[TODO]
  Matrix operator=(const Matrix &a);        //[TODO]
};

std::ostream &operator<<(std::ostream &os, const Matrix &m);

class MatrixChain {
 private:
  int num;

 public:
  Matrix *arr[100];

  MatrixChain(int matrixNum) { num = matrixNum; }
  Matrix calc(int l, int r) const;
  Matrix *setMatrix(int x, int row, int col) {
    arr[x] = new Matrix(row, col);
    return arr[x];
  }
};

///////////////////////////////////////////////////////////////

Matrix Matrix::operator*(const Matrix &a) const {
    Matrix temp(this->size_row, a.size_col);

    for (int i = 0 ; i < this->size_row ; i++)
        for (int j = 0 ; j < a.size_col ; j++)
            temp.arr[i][j] = 0;

    for (int i = 0 ; i < this->size_row ; i++)
        for (int j = 0 ;  j < a.size_col ; j++)
            for (int k = 0 ; k <this->size_col ; k++)
                temp.arr[i][j] += this->arr[i][k] * a.arr[k][j];

    return temp;
}

Matrix Matrix::operator=(const Matrix &a) {
    this->size_row = a.get_size_row();
    this->size_col = a.get_size_col();

    for (int i = 0 ; i < this->size_row ; i++)
        for (int j = 0 ; j < this->size_col ; j++)
            this->arr[i][j] = a.arr[i][j];
    return *this;
}

Matrix MatrixChain::calc(int l, int r) const {
    for (int i = l ; i <= r-1; i++)
        *arr[l] = (*arr[l]) * (*arr[i]);
    return *arr[l];
}
