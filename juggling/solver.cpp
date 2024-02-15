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

pair<int,int> find(vector<deque<int>> &d, int n, int f) {
    for (int i = 0; i < n; i++) {
        if (d[i].size() > 1) {
            int b;
            if (f == d[i].back()) {
                b = d[i].front();
                d[i].pop_front();
            } else {
                b = d[i].back();
                d[i].pop_back();
            }
            return {b, (i-b+n)%n};
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
        tie(a,x) = find(d,n,-1);
        int f = -1;
        while (true) {
            int b, y;
            tie(b,y) = find(d,n,f);
            f = b;
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
