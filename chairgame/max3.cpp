#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> v(n);
        vector<int> c(n+1);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            c[v[i]]++;
        }

        if (c[1] == n || c[2] == n || c[3] == n) {
            cout << "YES\n";
            for (auto x : v) cout << x << " ";
            cout << "\n";
        } else if (c[1] == c[3]) {
            cout << "YES\n";
            while (c[1]) {
                cout << "3 1 ";
                c[1]--;
            }
            while (c[2]) {
                cout << "2 ";
                c[2]--;
            }
            cout << "\n";
        } else {
            cout << "NO\n";
        }

    }
}
