#include <bits/stdc++.h>

using namespace std;

#define INF 999999999

int n, m, k;

int hotel[200001];
vector<vector<int>> graph;

int bfs(int x) {
    vector<int> queue;
    vector<int> dist(n+1);

    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[x] = 0;
    queue.push_back(x);

    for (int i = 0; i < (int)queue.size(); i++) {
        int c = queue[i];
        if (hotel[c] && dist[c] != 0) return dist[c];

        for (auto nc : graph[c]) {
            if (dist[c]+1 < dist[nc]) {
                dist[nc] = dist[c]+1;
                queue.push_back(nc);
            }
        }
    }

    return -1;
}

int main() {
    cin >> n >> m >> k;

    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        hotel[x] = 1;
    }

    graph.resize(n+1);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        cout << bfs(i) << " ";
    }
    cout << "\n";
}
