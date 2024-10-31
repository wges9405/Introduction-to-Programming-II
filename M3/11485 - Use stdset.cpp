#include <iostream>
#include <stdio.h>
#include <set>
#include <vector>
using namespace std;

vector<int> readVector () {
    int buffer;
    vector<int> temp;
    while (cin >> buffer && buffer != 0)
        temp.push_back(buffer);
    return temp;
}
int getvalue (vector<int> temp) {
    int value = 0;
    for (int i = 0 ; i < temp.size() ; i++)
        value += temp[i] * (temp.size()-i);
    return value;
}
vector<int> reverse(vector<int> temp) {
    vector<int> re_temp;
    for (int i = temp.size()-1 ; i >= 0 ; i--)
        re_temp.push_back(temp[i]);
    return re_temp;
}
void printVector (vector<int> temp) {
    for (int i = 0 ; i < temp.size() ; i++)
        cout << temp[i] << ' ';
    cout << endl;
}
struct mycompare {
    bool operator()(const vector<int>& lhs, const vector<int>& rhs) const {
        return getvalue(lhs) < getvalue(rhs);
    }
};

int main () {
    set<vector<int>, mycompare> M;
    string command;

    while (cin >> command) {
        if (command == "insert") {
            bool done = false;
            vector<int> temp = readVector();
            for (set<vector<int>, mycompare>::iterator it = M.begin() ; it != M.end() ; it++) {
                vector<int> current = *it;
                if (getvalue(temp) == getvalue(current)) {
                    done  = true;
                    cout << "exits" << endl;
                    M.erase(current);
                    M.insert(reverse(temp));
                    break;
                }
            }
            if (!done) M.insert(temp);
        }
        else if (command == "range_out") {
            int begin = getvalue(readVector());
            int end = getvalue(readVector());

            for (set<vector<int>, mycompare>::iterator it = M.begin() ; it != M.end() ; it++) {
                vector<int> current = *it;
                int key_value = getvalue(current);
                if (key_value >= begin && key_value <= end) printVector(current);
                else if (key_value > end) break;
            }
        }
        else if (command == "output") {
            for (set<vector<int>, mycompare>::iterator it = M.begin() ; it != M.end() ; it++) {
                vector<int> current = *it;
                printVector(current);
            }
        }
    }
}
