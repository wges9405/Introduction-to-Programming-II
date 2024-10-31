#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// G[i] is the neighbor towns of town i
vector<int> diamondTowns;
vector<int> G[100005];
int Dist[100005];

struct node {
private:
    int id;
    int dist;
public:
    node(int id, int l) {
        this->id = id;
        this->dist = l;
    }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        diamondTowns.push_back(x);
    }
    fill(Dist, Dist+100005, -1);

    queue<node> Q;

    // [TODO] complete the task!
    for (int num : diamondTowns)
        Q.push(node(num, 0));
    while (!Q.empty()) {
        node current = Q.front();
        Q.pop();
        if (Dist[current.id] == -1) {
            Dist[current.id] = current.dist;
            for (int next_town : G[current.id])
                Q.push(node(next_town, current.dist+1));
        }
    }

    // Output
    for (int i = 1; i <= N; i++) {
        cout << Dist[i] << '\n';
    }
    return 0;
}
