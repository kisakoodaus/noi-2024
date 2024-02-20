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

  auto foradj = [=](pair<int, int> x, auto f) {
    auto [a, b] = x;
    if (a > 0) f((a-1), b);
    if (b > 0) f(a, (b-1));
    if (a < n-1) f((a+1), b);
    if (b < m-1) f(a, (b+1));
  };

  vector<vector<int>> d(n, vector<int>(m, 1));

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
    vector<pair<int, int>> cands;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
      if (i == 0 || j == 0 || i == n-1 || j == m-1)
        cands.push_back({i, j});
    }
    shuffle(cands);
    cands.resize(min(int(5.*n*m/maxd), (n+m)/8));
    for (auto [sa, sb] : cands) {
      vector<pair<int, int>> q;
      q.push_back({sa, sb});
      vector<vector<int>> z(n, vector<int>(m));
      z[sa][sb] = 1;
      int res = rnd(maxd/2, cap);
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
    add_noise(d, maxd, 0.02);
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
