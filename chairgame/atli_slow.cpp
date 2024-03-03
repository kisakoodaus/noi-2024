#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

void adjust(vi &v, int i, int j, int x) {
    int n = v.size();
    vi w(n);
    for(int k = 0; k < n; ++k)
        w[k] = (v[k] + k) % n;
    int a0 = i, a1 = j, b0 = v[i], b1 = v[j], c0 = w[i], c1 = w[j];
    b0 = (b0 + x) % n;
    b1 = (b1 + n - x) % n;
    while(true) {
        if((a0 + b0) % n == c0) {
            v[a0] = b0; w[a0] = c0;
            v[a1] = b1; w[a1] = c1;
            break;
        } else if((a0 + b1) % n == c0) {
            v[a0] = b1; w[a0] = c0;
            v[a1] = b0; w[a1] = c1;
            break;
        } else if((a0 + b0) % n == c1) {
            v[a0] = b0; w[a0] = c1;
            v[a1] = b1; w[a1] = c0;
            break;
        } else if((a0 + b1) % n == c1) {
            v[a0] = b1; w[a0] = c1;
            v[a1] = b0; w[a1] = b0;
            break;
        } else {
            int y = (c0 - b0 + n) % n;
            int b2 = v[y], c2 = w[y];
            v[y] = b0; w[y] = c0;
            b0 = b2; c0 = c1; c1 = c2;
        }
    }
}

vi make_juggle(vi qual) {
    int n = qual.size();
    map<int,int> cnts;
    for(int i = 0; i < n; ++i) {
        if(!cnts.count(qual[i])) cnts[qual[i]] = 0;
        cnts[qual[i]]++;
    }
    vi cur(n, 0);
    while(true) {
        int i = -1, j = -1;
        map<int,int> cp = cnts;
        for(int k = 0; k < n; ++k) {
            if(cp.count(cur[k])) cp[cur[k]]--;
            if(!cp.count(cur[k]) || cp[cur[k]] < 0) {
                if(i == -1) i = k;
                else if(j == -1) j = k;
            }
        }
        int x = -1;
        for(auto p : cp) if(p.second > 0) x = p.first;
        if(x == -1) break;
        adjust(cur, i, j, (x - cur[i] + n) % n);
    }
    return cur;
}

vi adjust_mod(vi inp) {
    int n = inp.size();
    for(int i = 0; i < n; ++i)
        if(inp[i] == n) inp[i] = 0;
    vi res = make_juggle(inp);
    for(int i = 0; i < n; ++i)
        if(res[i] == 0) res[i] = n;
    return res;
}

int main() {
    int n, t; cin >> t;
    while(t--) {
        cin >> n;
        vi v(n); int sm = 0;
        for(int i = 0; i < n; ++i) {
            cin >> v[i];
            sm += v[i];
            sm %= n;
        }
        if(sm == 0) {
            cout << "YES\n";
            for(int x : adjust_mod(v)) cout << x << ' ';
            cout << '\n';
        } else {
            cout << "NO\n";
        }
    }
}
