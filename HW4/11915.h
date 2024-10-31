#include <iostream>

class Vector {
private:
    int v_size;
    int *v;
public:
    Vector() {
        v_size = 0;
        v = NULL;
    }
    Vector(int n) {
        v_size = n;
        v = new int[n];
    }
    ~Vector() {
        delete [] v;
    }
    void read() {
        for (int i = 0; i < v_size; i++) {
            std::cin >> v[i];
        }
    }
    void set(int index, int value) {
        if (index < 0 || index >= v_size) {
            std::cout << "OUT OF BOUND\n";
            return;
        }
        else v[index] = value;
    }
    const int size() const;

    Vector operator+(const Vector& a);

    Vector operator-(const Vector& a);

    // return the value of v[index]
    const int operator[](int index) const;

    // Dot product
    int operator*(const Vector& a);

};

// Print the Vector
std::ostream& operator<<(std::ostream& os, const Vector& v);

//////////////////////////////////////////////////////////////////////

const int Vector::size() const {
    return this->v_size;
}

Vector Vector::operator+(const Vector& a) {
    Vector temp(a.v_size);
    for (int i = 0 ; i < a.v_size ; i++)
        temp.v[i] = v[i] + a.v[i];
    return temp;
}
Vector Vector::operator-(const Vector& a) {
    Vector temp(a.v_size);
    for (int i = 0 ; i < a.v_size ; i++)
        temp.v[i] = v[i] - a.v[i];
    return temp;
}
const int Vector::operator[](int index) const {
    return this->v[index];
}
int Vector::operator*(const Vector& a) {
    int ans = 0;
    for (int i = 0 ; i < a.v_size ; i++)
        ans += v[i] * a.v[i];
    return ans;
}
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    for (int i = 0 ; i < v.size() ; i++)
        os << v[i] << " ";
    return os;
}

/*
I:
3
ADD 2
1 2 
1 2 
SUB 3
1 2 3 
2 3 4 
DOT 2
1 2 
1 1

O:
2 4 
-1 -1 -1 
3 
*/