#include <bits/stdc++.h>

using namespace std;

#define INF 999999999

int n, m, k;

int hotel[200001];
vector<pair<int,int>> roads;
vector<vector<int>> graph;

pair<int,int> status[200001];
int result[200001];

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
        roads.push_back({a,b});
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> queue;
    for (int i = 1; i <= n; i++) {
        result[i] = INF;
        if (hotel[i]) {
            queue.push_back(i);
            status[i] = {i,0};
        }
    }

    for (int i = 0; i < (int)queue.size(); i++) {
        int c = queue[i];

        for (auto nc : graph[c]) {
            if (status[nc].first == 0) {
                queue.push_back(nc);
                status[nc] = {status[c].first,status[c].second+1};
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (status[i].second != 0) {
            result[i] = status[i].second;
        }
    }

    for (auto r : roads) {
        int c1 = status[r.first].first;
        int c2 = status[r.second].first;
        if (c1 != c2) {
            int d = status[r.first].second+status[r.second].second+1;
            result[c1] = min(result[c1], d);
            result[c2] = min(result[c2], d);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (result[i] == INF) result[i] = -1;
        cout << result[i] << " ";
    }
    cout << "\n";
}
