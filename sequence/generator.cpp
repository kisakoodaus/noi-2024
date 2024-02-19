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

set<vector<int>> small;

void create(int n, vector<int> v) {
    if ((int)v.size() == n) {
        sort(v.begin(),v.end());
        small.insert(v);
        return;
    }
    for (int i = 1; i <= n; i++) {
        auto u = v;
        u.push_back(i);
        create(n, u);
    }
}

int main(int argc, char **argv)
{
    // Check argument count
    if (argc != 4)
        usage();

    // Parse arguments into numbers
    unsigned long long seed = stoull(argv[1]);
    r_dev.seed(seed);
    r_dev64.seed(seed);

    string what = argv[2];
    int n = atoi(argv[3]);

    int t_max = 1000;

    if (what == "small") {
        for (int i = 1; i <= n; i++) {
            create(i, {});
        }
        cout << small.size() << "\n";
        for (auto s : small) {
            random_shuffle(s.begin(),s.end());
            int u = s.size();
            cout << u << "\n";
            for (int i = 0; i < u; i++) {
                cout << s[i];
                cout << " \n"[i == u-1];
            }
        }
    }
    if (what == "random-possible") {
        cout << t_max << "\n";
        for (int k = 1; k <= t_max; k++) {
            cout << n << "\n";
            vector<int> s;
            int sum = 0;
            for (int i = 1; i <= n; i++) {
                int x = rnd(1, n);
                if (i == n) x = n-sum%n;
                sum += x;
                s.push_back(x);
            }
            for (int i = 0; i < n; i++) {
                cout << s[i];
                cout << " \n"[i == n-1];
            }
        }
    }
    if (what == "random-any") {
        cout << t_max << "\n";
        for (int k = 1; k <= t_max; k++) {
            cout << n << "\n";
            vector<int> s;
            for (int i = 1; i <= n; i++) {
                int x = rnd(1, n);
                s.push_back(x);
            }
            for (int i = 0; i < n; i++) {
                cout << s[i];
                cout << " \n"[i == n-1];
            }
        }
    }
    if (what == "distinct") {
        cout << n << "\n";
        for (int k = 1; k <= n; k++) {
            cout << k << "\n";
            vector<int> s;
            for (int i = 1; i <= k; i++) {
                s.push_back(i);
            }
            random_shuffle(s.begin(), s.end());
            for (int i = 0; i < k; i++) {
                cout << s[i];
                cout << " \n"[i == k-1];
            }
        }
    }
    if (what == "max5") {
        cout << t_max << "\n";
        for (int k = 1; k <= t_max; k++) {
            cout << n << "\n";
            vector<int> s;
            for (int i = 1; i <= n; i++) {
                s.push_back(3);
            }
            for (int z = 1; z <= 1e5; z++) {
                int a = rnd(0,n-1);
                int b = rnd(0,n-1);
                if (a != b && s[a]-1 >= 1 && s[b]+1 <= 5) {
                    s[a]--;
                    s[b]++;
                }
            }
            for (int i = 0; i < n; i++) {
                cout << s[i];
                cout << " \n"[i == n-1];
            }
        }
    }
    if (what == "minimum") {
        cout << n << "\n";
        for (int k = 1; k <= n; k++) {
            cout << k << "\n";
            for (int i = 1; i <= k; i++) {
                cout << 1;
                cout << " \n"[i == k];
            }
        }
    }
    if (what == "maximum") {
        cout << n << "\n";
        for (int k = 1; k <= n; k++) {
            cout << k << "\n";
            for (int i = 1; i <= k; i++) {
                cout << k;
                cout << " \n"[i == k];
            }
        }
    }
}
