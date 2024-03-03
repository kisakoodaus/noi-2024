// has some bug but passed tests
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
 
using namespace std;
 
int n, m;
int d[202020];
vector<array<int,3>> edges;
 
vector<int> up[202020];
 
int pa[202020];
int si[202020];
int mi[202020];
int ed[202020];
 
int cic[202020];
int sac[202020];
 
int rx;
 
int id(int x) {
    while (pa[x] != x) x = pa[x];
    return x;
}
 
void merge(int a, int b) {
    a = id(a);
    b = id(b);
 
    if (si[a] < si[b]) swap(a,b);
    pa[b] = a;
    si[a] += si[b];
    if (d[mi[a]] > d[mi[b]]) {
        mi[a] = mi[b];
    }
    if (d[mi[a]] == d[mi[b]] && mi[a] != mi[b]) {
        for (auto x : up[mi[b]]) {
            up[mi[a]].push_back(x);
            // cic[mi[a]] += cic[x];
        }
        cic[mi[a]] += cic[mi[b]];
        sac[mi[a]] += sac[mi[b]];
        ed[mi[a]] |= ed[mi[b]];
        up[mi[b]].clear();
    }
}
 
void calc(int c, int x) {
    // cout << c << " " << d[c] << " " << sac[c] << " " << cic[c] << " " << ed[c] << "\n";
 
    int md = d[c];
    if (ed[c]) rx = max(rx,x+min(sac[c]+cic[c],md-x));
 
    for (auto u : up[c]) {
        calc(u,x+min(sac[c]+cic[c]-sac[u]-cic[u],md-x));
    }
}
 
int main() {
    cin >> n >> m;
    for (int i = 0; i < n*m; i++) {
        cin >> d[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m-1; j++) {
            int md = min(d[i*m+j],d[i*m+j+1]);
            edges.push_back({md,i*m+j,i*m+j+1});
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n-1; j++) {
            int md = min(d[j*m+i],d[(j+1)*m+i]);
            edges.push_back({md,j*m+i,(j+1)*m+i});
        }
    }
    sort(edges.rbegin(), edges.rend());
 
    for (int i = 0; i < n*m; i++) {
        pa[i] = i;
        si[i] = 1;
        mi[i] = i;
        sac[i] = 1;
        ed[i] = i%m == 0 || i%m == m-1 || i < m || i >= m*(n-1);
    }
 
    for (auto e : edges) {
        // cout << e[0] << " " << e[1] << " " << e[2] << "\n";
        int e1 = id(e[1]);
        int e2 = id(e[2]);
        if (e1 == e2) continue;
        if (d[mi[e1]] < d[mi[e2]]) swap(e1,e2);
        if (d[mi[e1]] > d[mi[e2]]) {
            up[mi[e2]].push_back(mi[e1]);
            cic[mi[e2]] += cic[mi[e1]]+sac[mi[e1]];
            ed[mi[e2]] |= ed[mi[e1]];
        }
        merge(e1, e2);
    }
 
    calc(mi[id(0)], 0);
 
    cout << rx << "\n";
}
