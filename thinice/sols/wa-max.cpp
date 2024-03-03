// WA
// should only pass a few tests where the answer is equal to maxd
// TODO: passes tests 3 & 4
#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m;
  cin >> n >> m;
  int mx = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    int v;
    cin >> v;
    mx = max(mx, v);
  }
  cout << mx << endl;
}
