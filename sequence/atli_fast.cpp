#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int,bool> ib;
typedef vector<ib> vib;
#define fs first
#define sd second

struct perm {
    vib dat;
    set<int> rem_inds;

    perm(int n) : dat(vib(n, make_pair(0, false))) {
        rem_inds = set<int>();
        for(int i = 0; i < n; ++i)
            rem_inds.insert(i);
    }

    void pswap(int i, int j) {
        if(dat[i].sd && !dat[j].sd) {
            rem_inds.insert(i);
            rem_inds.erase(j);
        }
        if(!dat[i].sd && dat[j].sd) {
            rem_inds.erase(i);
            rem_inds.insert(j);
        }
        swap(dat[i], dat[j]);
    }

    int val(int i) {
        return dat[i].fs;
    }

    bool done(int i) {
        return dat[i].sd;
    }

    void put(int i, int x, bool wanted) {
        dat[i].fs = x;
        if(!dat[i].sd && wanted) rem_inds.erase(i);
        if(dat[i].sd && !wanted) rem_inds.insert(i);
        dat[i].sd = wanted;
    }
};

void adjust(perm &p, int i, int j, int x, bool want) {
    int n = p.dat.size();
    int a0 = i, a1 = j;
    int b0 = (p.val(i) + x) % n, b1 = ((p.val(j) - x) % n + n) % n;
    int c0 = (p.val(i) + i) % n, c1 = (p.val(j) + j) % n;
    p.put(i, b0, true);
    p.put(j, b1, want);
    while(true) {
        if((a0 + b0) % n == c0 % n || (a0 + b0) % n == c1 % n) {
            return;
        } else if((a0 + b1) % n == c0 % n || (a0 + b1) % n == c1 % n) {
            p.pswap(a0, a1);
            return;
        } else {
            int y = ((c0 - b0) % n + n) % n;
            int b2 = p.val(y), c2 = (p.val(y) + y) % n;
            p.pswap(y, a0);
            b0 = b2; c0 = c1; c1 = c2;
        }
    }
}

vi make_juggle(vi qual) {
    int n = qual.size();
    multiset<int> remaining;
    perm p(n);
    int zer = 0;
    for(int x : qual) {
        if(x == 0) p.put(zer++, 0, true);
        else remaining.insert(x);
    }
    while(remaining.size() > 0) {
        int x = *remaining.begin();
        remaining.erase(remaining.begin());
        int i = -1, j = -1;
        for(int jposs : p.rem_inds) {
            int iposs = ((p.val(jposs) + jposs - x) % n + n) % n;
            if(p.done(iposs)) continue;
            i = iposs; j = jposs;
            break;
        }
        if(i == -1 || j == -1) {
            i = *p.rem_inds.begin();
            j = *(++p.rem_inds.begin());
        }
        int z = ((x - p.val(i)) % n + n) % n;
        int y = (p.val(j) - z + n) % n;
        bool want = remaining.count(y);
        assert(i != -1 && j != -1);
        adjust(p, i, j, z, want);
        if(want) remaining.erase(remaining.find(y));
    }
    vi ret(n);
    for(int i = 0; i < n; ++i)
        ret[i] = p.val(i);
    return ret;
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
