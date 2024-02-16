#include <bits/stdc++.h>

using namespace std;

bool check(vector<int> s) {
    int n = s.size();
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        int k = (s[i]+i)%n;
        if (c[k]) return false;
        c[k] = 1;
    }
    return true;
}

pair<int,int> find(vector<deque<int>> &d) {
    int n = d.size();
    for (int i = 0; i < n; i++) {
        if (d[i].size() > 1) {
            int f = d[i].front();
            d[i].pop_front();
            return {f, (i-f+n)%n};
        }
    }
    return {0,0};
}

vector<int> create(vector<int> s) {
    int n = s.size();
    while (!check(s)) {
        vector<deque<int>> d(n);
        for (int i = 0; i < n; i++) {
            int k = (s[i]+i)%n;
            d[k].push_back(s[i]);
        }
        int a, x;
        tie(a,x) = find(d);
        while (true) {
            int b, y;
            tie(b,y) = find(d);
            s[x] = b;
            d[(x+b)%n].push_back(b);
            if (d[(x+b)%n].size() == 1) {
                s[y] = a;
                d[(y+a)%n].push_back(a);
                break;
            }
            x = y;
        }
    }
    return s;
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
        cout << "YES\n";
        auto c = create(s);
        for (auto x : c) cout << x << " ";
        cout << "\n";
    }
}
