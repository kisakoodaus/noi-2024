#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator seed n m dmax type" << endl;
    exit(1);
}

mt19937 r_dev;
mt19937_64 r_dev64;
// Returns a value in range [0, 1[
double rnd()
{
    return uniform_real_distribution<double>(0, 1)(r_dev);
}
// Returns a value in range [a, b] inclusive
int rnd(int a, int b)
{
    return uniform_int_distribution<int>(a, b)(r_dev);
}
long long rnd64(long long a, long long b)
{
    return uniform_int_distribution<long long>(a, b)(r_dev64);
}
// Returns either 0 or 1
int coin()
{
    return rnd(0, 1);
}
// Shuffles any type with begin and end
template <typename T>
void shuffle(T &arr)
{
    shuffle(arr.begin(), arr.end(), r_dev);
}

void add_noise(vector<vector<int>> &d, int maxd, double par) {
  binomial_distribution<> dist(maxd-1, par);
  for (auto &row : d) {
    for (int &v : row) {
      v += dist(r_dev);
      v = min(v, maxd);
    }
  }
}

void add_bfs(vector<vector<int>> &d, pair<int, int> start, int res) {
  int n = d.size(), m = d[0].size();
  auto foradj = [=](pair<int, int> x, auto f) {
    auto [a, b] = x;
    if (a > 0) f((a-1), b);
    if (b > 0) f(a, (b-1));
    if (a < n-1) f((a+1), b);
    if (b < m-1) f(a, (b+1));
  };
  auto [sa, sb] = start;
  vector<pair<int, int>> q;
  q.push_back(start);
  vector<vector<int>> z(n, vector<int>(m));
  z[sa][sb] = 1;
  for (int val = res; val >= 1; --val) {
    int qi = rnd(0, q.size()-1);
    auto x = q[qi];
    auto [xa, xb] = x;
    swap(q[qi], q.back());
    q.pop_back();
    d[xa][xb] = max(val, d[xa][xb]);
    foradj(x, [&](int ya, int yb) {
      if (z[ya][yb]) return;
      z[ya][yb] = 1;
      q.push_back({ya, yb});
    });
  }
}

struct Solver {
  int n, m, nm;
  vector<int> d, p, cs, dp, ord_u, ord_d;
  vector<vector<int>> v;
  int res;
  Solver(vector<vector<int>> &d_rect)
    : n(d_rect.size()), m(d_rect[0].size()), nm(n*m),
    p(nm), cs(nm), dp(nm), ord_u(nm), v(nm)
  {
    for (auto &rw : d_rect) {
      for (int x : rw) d.push_back(x);
    }
  }
  int getp(int i);
  template<typename T>
  void foradj(int i, T f);
  bool atedge(int i);
  void solve();
  vector<vector<int>> chokepoints();
};

int main(int argc, char **argv)
{
  // Check argument count
  if (argc < 6 || argc > 7)
      usage();

  // Parse arguments into numbers
  unsigned long long seed = stoull(argv[1]);
  r_dev.seed(seed);
  r_dev64.seed(seed);
  int n = atoi(argv[2]);
  int m = atoi(argv[3]);
  int maxd = atoi(argv[4]);
  string tp = argv[5];

  vector<vector<int>> d(n, vector<int>(m, 1));

  vector<pair<int, int>> edges;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (i == 0 || j == 0 || i == n-1 || j == m-1)
      edges.push_back({i, j});
  }

  if (tp == "rand") {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        d[i][j] = rnd(1, maxd);
      }
    }
  } else if (tp == "bin") {
    double par = stod(argv[6]);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        d[i][j] = rnd(1, maxd/5);
      }
    }
    add_noise(d, maxd, par);
  } else if (tp == "bfs") {
    int cap;
    if (argc >= 7) cap = atoi(argv[6]);
    else cap = rnd(maxd*4/5, maxd);
    auto cands = edges;
    shuffle(cands);
    cands.resize(min(int(5.*n*m/maxd), (n+m)/8));
    for (auto st : cands) {
      add_bfs(d, st, rnd(maxd/2, cap));
    }
    add_noise(d, maxd, 0.02);
  } else if (tp == "choke") {
    assert(argc >= 7);
    int cap = atoi(argv[6]);
    bool single_sol = cap < 0;
    cap = abs(cap);
    if (single_sol) cap--;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        d[i][j] = rnd(1, cap-1);
      }
    }
    auto prevd = d;
    for (int rep = 0; rep < 50; ++rep) {
      Solver slv(d);
      slv.solve();
      auto choke = slv.chokepoints();
      if (slv.res > cap) {
        d = prevd;
        assert(rep > 30);
        break;
      }
      prevd = d;
      vector<pair<int, int>> cands;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          if (!choke[i][j] && d[i][j] < maxd) {
            cands.push_back({i, j});
          }
        }
      }
      shuffle(cands);
      vector<vector<int>> z(n, vector<int>(m));
      for (auto [i, j] : cands) {
        if (z[i][j]) continue;
        d[i][j]++;
        for (int di = -10*cap; di <= 10*cap; ++di) {
          for (int dj = -10*cap; dj <= 10*cap; ++dj) {
            if (i+di < 0 || i+di >= n || j+dj < 0 || j+dj >= m) continue;
            z[i+di][j+dj] = 1;
          }
        }
      }
    }
    if (single_sol) {
      add_bfs(d, edges[rnd(0, edges.size()-1)], cap+1);
    }
  } else {
    throw;
  }

  cout << n << " " << m << "\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << d[i][j];
      if (j != m-1) cout << " ";
    }
    cout << "\n";
  }
}

int Solver::getp(int i) {
  while (i != p[i]) {
    p[i] = p[p[i]];
    i = p[i];
  }
  return i;
}
template<typename T>
void Solver::foradj(int i, T f) {
  int a = i / m, b = i % m;
  if (a > 0) f((a-1)*m + b);
  if (b > 0) f(a*m + (b-1));
  if (a < n-1) f((a+1)*m + b);
  if (b < m-1) f(a*m + (b+1));
}
bool Solver::atedge(int i) {
  int a = i / m, b = i % m;
  return a == 0 || b == 0 || a == n-1 || b == m-1;
}

void Solver::solve() {
  vector<int> z(nm);
  for (int i = 0; i < nm; ++i) {
    p[i] = i;
    ord_u[i] = i;
  }
  sort(ord_u.begin(), ord_u.end(), [&](int a, int b) { return d[a] > d[b]; });
  ord_d = ord_u;
  reverse(ord_d.begin(), ord_d.end());
  for (int i : ord_u) {
    z[i] = 1;
    foradj(i, [&](int j) {
        if (!z[j]) return;
        int x = getp(j);
        if (x == i) return;
        p[x] = i;
        v[i].push_back(x);
    });
  }
  for (int i : ord_u) {
    cs[i] = 1;
    for (int j : v[i]) {
      cs[i] += cs[j];
    }
  }
  res = 0;
  for (int i : ord_d) {
    if (atedge(i)) {
      res = max(res, min(dp[i] + cs[i], d[i]));
    }
    for (int j : v[i]) {
      dp[j] = min(dp[i] + cs[i] - cs[j], d[i]);
    }
  }
}

vector<vector<int>> Solver::chokepoints() {
  vector<int> z(nm), choke(nm);
  for (int i : ord_u) {
    if (atedge(i) && min(dp[i] + cs[i], d[i]) == res) {
      if (dp[i] + cs[i] > d[i]) {
        choke[i] = 1;
      } else {
        z[i] = 1;
      }
    }
    for (int j : v[i]) {
      if (z[j]) {
        if (dp[i] + cs[i] - cs[j] > d[i]) {
          choke[i] = 1;
        } else {
          z[i] = 1;
        }
      }
    }

  }
  vector<vector<int>> ret(n, vector<int>(m));
  for (int i = 0; i < nm; ++i) {
    ret[i/m][i%m] = choke[i];
  }
  return ret;
}
