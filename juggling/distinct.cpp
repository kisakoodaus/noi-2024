#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int x;
        for (int i = 0; i < n; i++) cin >> x;

        if (n%2 == 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (int i = 1; i <= n; i++) cout << i << " ";
            cout << "\n";
        }

    }
}
