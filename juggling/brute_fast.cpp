#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> s, r, g;
bool found;

void search(int k) {
    if (found) return;
    if (k == n) {
        found = true;
        cout << "YES\n";
        for (int i = 0; i < n; i++) cout << r[i] << " ";
        cout << "\n";
        return;
    }
    for (int i = 0; i < n-k; i++) {
        int u = (k+s[i])%n;
        if (g[u]) continue;
        r[k] = s[i];
        g[u] = 1;
        swap(s[i], s[n-k-1]);
        search(k+1);
        g[u] = 0;
        swap(s[i], s[n-k-1]);
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        cin >> n;

        s.resize(n);
        r.resize(n);
        g.resize(n);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            sum += s[i];
            g[i] = 0;
        }

        found = false;
        if (sum%n == 0) search(0);

        if (!found) cout << "NO\n";
    }
}
