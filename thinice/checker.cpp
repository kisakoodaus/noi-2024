#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int main() {
  auto v = read_ints(2, 1, 1000000);
  long n = v[0], m = v[1];
  long nm = n*m;
  if (nm > 1000000) fail();
  long maxd = 0;
  for (int i = 0; i < n; ++i) {
    auto d = read_ints(m, 1, 1000000);
    maxd = max(maxd, (long)*max_element(d.begin(), d.end()));
  }
  vector<int> g;
  if (nm <= 16 && maxd <= 16) g.push_back(1);
  if (n == 1 && m <= 1e6) g.push_back(2);
  if (maxd <= 5) g.push_back(3);
  if (nm <= 1024 && maxd <= 1024) g.push_back(4);
  g.push_back(5);
  end_groups(g);
}
