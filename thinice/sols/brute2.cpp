// AC, slow but O(n) memory
// passes subtasks 1-4
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
struct phase {
  int cnt;
  vector<int> z, sz, dp, ce;
  phase(int nm) : cnt(2), z(nm, 1), sz{0, nm}, dp{0, 0}, ce{0, 1} {}
  int next() {
    sz.push_back(0);
    dp.push_back(0);
    ce.push_back(0);
    return cnt++;
  }
  void reset() {
    cnt = 1;
    fill(z.begin(), z.end(), 0);
    sz.resize(1);
    dp.resize(1);
    ce.resize(1);
  }
};
int main() {
  ios::sync_with_stdio();
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  int nm = n * m;
  auto foradj = [=](int i, auto f) {
    int a = i / m, b = i % m;
    if (a > 0) f((a-1)*m + b);
    if (b > 0) f(a*m + (b-1));
    if (a < n-1) f((a+1)*m + b);
    if (b < m-1) f(a*m + (b+1));
  };
  auto atedge = [=](int i) {
    int a = i / m, b = i % m;
    return a == 0 || b == 0 || a == n-1 || b == m-1;
  };
  vector<int> d(nm), ord(nm), da(nm);
  phase cur(nm), nxt(nm);
  vector<int> q;
  for (int i = 0; i < nm; ++i) {
    cin >> d[i];
    ord[i] = i;
  }
  sort(ord.begin(), ord.end(), [&](int a, int b) {return d[a] < d[b];});
  int res = 0;
  for (int ordi = 0; ordi < nm; ++ordi) {
    int dav = d[ord[ordi]];
    da[ord[ordi]] = 1;
    if (ordi == nm-1 || dav != d[ord[ordi+1]]) {
      for (int g = 1; g < cur.cnt; ++g) {
        if (cur.ce[g])
          res = max(res, min(cur.dp[g] + cur.sz[g], dav));
      }
    }
    if (dav != d[ord[ordi+1]]) {
      nxt.reset();
      for (int i = 0; i < nm; ++i) {
        if (!cur.z[i] || da[i] || nxt.z[i]) continue;
        int w = nxt.next();
        q.clear();
        q.push_back(i);
        nxt.z[i] = w;
        bool can_exit = atedge(i);
        for (int qi = 0; qi < (int)q.size(); ++qi) {
          int x = q[qi];
          foradj(x, [&](int y) {
            if (!cur.z[y] || da[y] || nxt.z[y]) return;
            q.push_back(y);
            nxt.z[y] = w;
            can_exit |= atedge(y);
          });
        }
        nxt.sz[w] = q.size();
        int cw = cur.z[q[0]];
        nxt.dp[w] = min(cur.dp[cw] + cur.sz[cw] - nxt.sz[w], dav);
        nxt.ce[w] = can_exit;
      }
      fill(da.begin(), da.end(), 0);
      swap(cur, nxt);
    }
  }
  cout << res << endl;
}
