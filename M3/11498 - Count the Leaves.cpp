#include <iostream>
#include <set>
using namespace std;
int main () {
    set<int> mother;
    set<int> all;
    int N;

    while (cin >> N && N != 0) {
        while (N--) {
            int mom, son;
            cin >> mom >> son;
            all.insert(mom);
            all.insert(son);
            mother.insert(mom);
        }
        int root;
        cin >> root;
        cout << all.size() - mother.size() << endl;
        mother.clear();
        all.clear();
    }
}
