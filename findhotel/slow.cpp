#include <bits/stdc++.h>

using namespace std;

#define INF 999999999

int n, m, k;

int hotel[200001];
vector<vector<int>> graph;

int counter[200001];
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
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) result[i] = INF;

    vector<int> queue;
    vector<int> dist(n+1);

    for (int i = 1; i <= n; i++) {
        if (hotel[i]) {
            dist[i] = 0;
            queue.push_back(i);
        } else {
            dist[i] = INF;
        }
    }

    for (int i = 0; i < (int)queue.size(); i++) {
        int c = queue[i];
        if (!hotel[c]) result[c] = min(result[c], dist[c]);

        for (auto nc : graph[c]) {
            if (dist[c]+1 < dist[nc]) {
                dist[nc] = dist[c]+1;
                queue.push_back(nc);
            }
        }
    }

    for (int h = 1; h <= n; h++) {
        if (hotel[h]) {
            queue.clear();
            dist[h] = 0;
            counter[h] = h;
            queue.push_back(h);

            for (int i = 0; i < (int)queue.size(); i++) {
                int c = queue[i];
                if (hotel[c] && dist[c] != 0) {
                    result[h] = min(result[h], dist[c]);
                    break;
                }

                for (auto nc : graph[c]) {
                    if (counter[nc] != h || dist[c]+1 < dist[nc]) {
                        dist[nc] = dist[c]+1;
                        counter[nc] = h;
                        queue.push_back(nc);
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (result[i] == INF) result[i] = -1;
        cout << result[i] << " ";
    }
    cout << "\n";
}
