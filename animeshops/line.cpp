#include <bits/stdc++.h>

using namespace std;

#define INF 999999999

int n, m, k;

int hotel[200001];
int result[200001];

int main() {
    cin >> n >> m >> k;

    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        hotel[x] = 1;
    }

    for (int i = 1; i <= n; i++) result[i] = INF;

    int d = INF;
    for (int i = 1; i <= n; i++) {
        d++;
        result[i] = min(result[i], d);
        if (hotel[i]) d = 0;
    }

    d = INF;
    for (int i = n; i >= 1; i--) {
        d++;
        result[i] = min(result[i], d);
        if (hotel[i]) d = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (result[i] == INF) result[i] = -1;
        cout << result[i] << " ";
    }
    cout << "\n";
}
