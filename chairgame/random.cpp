#include <bits/stdc++.h>

using namespace std;

bool valid(vector<int> s) {
    int n = s.size();
    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        int k = (i+s[i])%n;
        if (p[k]) return false;
        p[k] = 1;
    }

    return true;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> s(n);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            sum += s[i];
        }

        if (sum%n != 0) {
            cout << "NO\n";
            continue;
        }

        while (true) {
            random_shuffle(s.begin(), s.end());
            if (valid(s)) break;
        }

        cout << "YES\n";
        for (auto x : s) cout << x << " ";
        cout << "\n";
    }
}
