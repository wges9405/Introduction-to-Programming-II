#include <iostream>
#include <queue>
#include <set>
using namespace std;

int step[11];

int gcd (int a, int b) {
    if (b == 0) return a;
    else return gcd(b,a%b);
}

int check (int stepNum, int target) {
    int x = step[0];
    for (int i = 1 ; i < stepNum ; i++)
        x = gcd(step[i],x);
    return target%x == 0;
}

int solved (int stepNum, int target) {
    queue<pair<int,int>> Q;
    set<int> passed;
    bool find = false;

    Q.push(make_pair(0,0));

    while (!Q.empty()) {
        if (find) break;

        pair<int,int> temp = Q.front();
        Q.pop();

        int current_loc = temp.first;
        int current_step = temp.second;

        if (passed.find(current_loc) != passed.end()) continue;
        else passed.insert(current_loc);
        for (int i = 0 ; i < stepNum ; i++) {
            if (current_loc - step[i] == target || current_loc + step[i] == target) {
                cout << current_step+1 << endl;
                find = true;
                break;
            }
            Q.push(make_pair(current_loc - step[i], current_step+1));
            Q.push(make_pair(current_loc + step[i], current_step+1));
        }
    }
}

int main () {
    int N;

    cin >> N;
    while (N--) {
        int stepNum, target;

        cin >> stepNum >> target;
        for (int i = 0 ; i < stepNum ; i++)
            cin >> step[i];
        if (check(stepNum, target)) solved(stepNum, target);
        else cout << "-1" << endl;
    }
}
/*
I:
3
2 10
2 3
1 3
2
2 3
4 5

O:
4
-1
3
*/
