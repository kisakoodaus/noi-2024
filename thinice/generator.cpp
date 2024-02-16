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

int main(int argc, char **argv)
{
    // Check argument count
    if (argc != 6)
        usage();

    // Parse arguments into numbers
    unsigned long long seed = stoull(argv[1]);
    r_dev.seed(seed);
    r_dev64.seed(seed);
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);
    int maxd = atoi(argv[4]);
    string tp = argv[5];

    vector<vector<int>> d(n, vector<int>(m));

    if (tp == "rand") {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          d[i][j] = rnd(1, maxd);
        }
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
