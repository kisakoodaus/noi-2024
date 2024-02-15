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
        for (int i = 0; i < n; i++) cin >> s[i];
        sort(s.begin(), s.end());

        bool found = false;
        do {
            if (valid(s)) {
                found = true;
                cout << "YES\n";
                for (auto x : s) cout << x << " ";
                cout << "\n";
                break;
            }
        } while (next_permutation(s.begin(), s.end()));

        if (!found) cout << "NO\n";
    }
}
