#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator seed number" << endl;
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
    unsigned long long seed = stoull(argv[1]);
    r_dev.seed(seed);
    r_dev64.seed(seed);

    string s = argv[2];
    int n = atoi(argv[3]);

    if (s == "random") {
        int m = atoi(argv[4]);
        int k = atoi(argv[5]);
        cout << n << " " << m << " " << k << "\n";

        vector<int> v;
        for (int i = 1; i <= n; i++) v.push_back(i);
        random_shuffle(v.begin(), v.end());
        for (int i = 1; i <= k; i++) {
            cout << v[i-1];
            cout << " \n"[i == k];
        }

        set<pair<int,int>> e;
        while ((int)e.size() < m) {
            int a = rnd(1, n-1);
            int b = rnd(a+1, n);
            if (e.count({a,b})) continue;
            e.insert({a,b});
            cout << a << " " << b << "\n";
        }
    }
    if (s == "line") {
        int m = n-1;
        int k = atoi(argv[4]);
        cout << n << " " << m << " " << k << "\n";

        vector<int> v;
        for (int i = 1; i <= n; i++) v.push_back(i);
        random_shuffle(v.begin(), v.end());
        for (int i = 1; i <= k; i++) {
            cout << v[i-1];
            cout << " \n"[i == k];
        }

        for (int i = 1; i <= n-1; i++) {
            cout << i << " " << i+1 << "\n";
        }
    }
    if (s == "star") {
        if (n%2 == 0) n--;
        int m = n-1;
        int k = n/2;
        cout << n << " " << m << " " << k << "\n";

        for (int i = 1; i <= k; i++) {
            cout << 2*i+1;
            cout << " \n"[i == k];
        }

        for (int i = 2; i <= n; i++) {
            if (i%2 == 0) cout << 1 << " " << i << "\n";
            else cout << i-1 << " " << i << "\n";
        }
    }
}
