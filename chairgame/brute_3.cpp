#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> s, r, g;
bool found;
int max_s;
int z;

void search(int k) {
    z++;
    if (found || z > 1e3) return;
    if (k == n) {
        found = true;
        cout << "YES\n";
        for (int i = 0; i < n; i++) cout << r[i] << " ";
        cout << "\n";
        return;
    }
    if (k >= max_s && g[k] == 0) return;
    int v = 0;
    for (int i = 0; i < n-k; i++) {
        if (v == s[i]) continue;
        int u = (k+s[i])%n;
        if (g[u]) continue;
        v = s[i];
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
            max_s = max(max_s, s[i]);
            g[i] = 0;
        }

        if (sum%n != 0) {
            cout << "NO\n";
            continue;
        }

        do {
            random_shuffle(s.rbegin(), s.rend());
            z = 0;
            found = false;
            search(0);
        } while (!found);
    }
}
