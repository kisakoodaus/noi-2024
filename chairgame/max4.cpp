#include <bits/stdc++.h>

using namespace std;

void solve(vector<int> c, vector<vector<int>> p) {
    cout << "YES\n";
    for (auto e : p) {
        while (true) {
            bool f = false;
            for (auto x : e) {
                if (c[x] == 0) f = true;
                c[x]--;
            }
            if (f) {
                for (auto x : e) c[x]++;
                break;
            }
            for (auto x : e) cout << x << " ";
        }
    }
    cout << "\n";
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> v(n);
        vector<int> c(n+1);
        int s = 0;
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            c[v[i]]++;
            s += v[i];
        }

        if (s%n != 0) {
            cout << "NO\n";
            continue;
        }

        int a = s/n;

        if (a == 1) solve(c, {{1}});
        if (a == 2) solve(c, {{4,1,1},{3,1},{2}});
        if (a == 3) solve(c, {{4,4,1},{4,2},{3}});
        if (a == 4) solve(c, {{4}});
    }
}
