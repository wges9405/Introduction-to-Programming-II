#include <iostream>
class Matrix {
private:
    int size;
    int **arr;
    int get_count;
public:
    Matrix(int n, int **data) {
        size = n;
        arr = data;
        get_count = 0;
    }
    int *get_row(int row) {
        int *tmparr = new int[size];
        for (int i = 0; i < size; i++) {
            tmparr[i] = arr[row][i];
        }
        get_count++;
        return tmparr;
    }
    int *get_column(int col) {
        int *tmparr = new int[size];
        for (int i = 0; i < size; i++) {
            tmparr[i] = arr[i][col];
        }
        get_count++;
        return tmparr;
    }
    int get_size() {
        return size;
    }
    void remove(int *array) {
        delete[] array;
        get_count--;
    }
    ~Matrix() {
        if (get_count != 0) {
            std::cout << "[ERROR] something not recylced!\n";
        }
    }
};

////////////////////////////////////////////////////////////////

int calculate(Matrix A, Matrix B) {
    int ans = 0;
    int size = A.get_size();
    for (int i = 0 ; i < size ; i++) {
        int *row = A.get_row(i);
        for (int j = 0 ; j < size ; j++) {
            int *col = B.get_column(j);
            for (int k = 0 ; k < size ; k++)
                ans += row[k]*col[k];
            B.remove(col);
        }
        A.remove(row);
    }
    return ans;
}
/*
I:
2
1 2 
3 4 
1 2 
1 2 

O:
30
*/