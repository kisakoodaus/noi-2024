#include <bits/stdc++.h>
using namespace std;
const int N = 1e6;
int d[N];
int p[N];
int getp(int i) {
  while (i != p[i]) {
    p[i] = p[p[i]];
    i = p[i];
  }
  return i;
}
vector<int> v[N];
int cs[N], dp[N];
int main() {
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
  vector<int> ord(nm), z(nm);
  for (int i = 0; i < nm; ++i) {
    cin >> d[i];
    p[i] = i;
    ord[i] = i;
  }
  sort(ord.begin(), ord.end(), [](int a, int b) { return d[a] > d[b]; });
  for (int i : ord) {
    z[i] = 1;
    foradj(i, [&](int j) {
        if (!z[j]) return;
        int x = getp(j);
        p[x] = i;
        v[i].push_back(x);
    });
  }
  for (int i : ord) {
    cs[i] = 1;
    for (int j : v[i]) {
      cs[i] += cs[j];
    }
  }
  reverse(ord.begin(), ord.end());
  int res = 0;
  for (int i : ord) {
    if (atedge(i)) {
      res = max(res, min(dp[i] + 1, d[i]));
    }
    for (int j : v[i]) {
      dp[j] = min(dp[i] + cs[i] - cs[j], d[i]);
    }
  }
  cout << res << endl;
}
