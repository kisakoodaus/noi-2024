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

void create(int n, vector<int> v, double p = false) {
    if ((int)v.size() == n) {
        if (p) {
            int s = 0;
            for (auto x : v) s += x;
            if (s%n != 0) return;
        }
        sort(v.begin(),v.end());
        small.insert(v);
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (v.size() && v.back() > i) continue;
        auto u = v;
        u.push_back(i);
        create(n, u, p);
    }
}

void create_max(int n, vector<int> v, int e_max, double p = false) {
    if ((int)v.size() == n) {
        if (p) {
            int s = 0;
            for (auto x : v) s += x;
            if (s%n != 0) return;
        }
        sort(v.begin(),v.end());
        small.insert(v);
        return;
    }
    for (int i = 1; i <= min(n,e_max); i++) {
        if (v.size() && v.back() > i) continue;
        auto u = v;
        u.push_back(i);
        create_max(n, u, e_max, p);
    }
}

int main(int argc, char **argv)
{
    unsigned long long seed = stoull(argv[1]);
    r_dev.seed(seed);
    r_dev64.seed(seed);

    string what = argv[2];

    int t_max = 1000;

    if (what == "small") {
        int a = atoi(argv[3]);
        int b = atoi(argv[4]);
        for (int i = a; i <= b; i++) {
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
    if (what == "small-possible") {
        int a = atoi(argv[3]);
        int b = atoi(argv[4]);
        for (int i = a; i <= b; i++) {
            create(i, {}, true);
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
        int n = atoi(argv[3]);
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
        int n = atoi(argv[3]);
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
        int n = atoi(argv[3]);
        cout << t_max << "\n";
        for (int k = 0; k < t_max; k++) {
            int u = k%n+1;
            cout << u << "\n";
            vector<int> s;
            for (int i = 1; i <= u; i++) {
                s.push_back(i);
            }
            random_shuffle(s.begin(), s.end());
            for (int i = 0; i < u; i++) {
                cout << s[i];
                cout << " \n"[i == u-1];
            }
        }
    }
    if (what == "all1") {
        int n = atoi(argv[3]);
        cout << t_max << "\n";
        for (int k = 0; k < t_max; k++) {
            int u = k%n+1;
            cout << u << "\n";
            for (int i = 1; i <= u; i++) {
                cout << 1;
                cout << " \n"[i == u];
            }
        }
    }
    if (what == "alln") {
        int n = atoi(argv[3]);
        cout << t_max << "\n";
        for (int k = 0; k < t_max; k++) {
            int u = k%n+1;
            cout << u << "\n";
            for (int i = 1; i <= u; i++) {
                cout << u;
                cout << " \n"[i == u];
            }
        }
    }
    if (what == "max-any") {
        int e_max = atoi(argv[3]);
        int n = atoi(argv[4]);
        cout << t_max << "\n";
        for (int k = 1; k <= t_max; k++) {
            cout << n << "\n";
            vector<int> s;
            for (int i = 1; i <= n; i++) {
                int x = rnd(1,e_max);
                s.push_back(x);
            }
            for (int i = 0; i < n; i++) {
                cout << s[i];
                cout << " \n"[i == n-1];
            }
        }
    }
    if (what == "max-possible") {
        int e_max = atoi(argv[3]);
        int n = atoi(argv[4]);
        cout << t_max << "\n";
        for (int k = 1; k <= t_max; k++) {
            cout << n << "\n";
            vector<int> s;
            int w = 0;
            for (int i = 1; i <= n; i++) {
                int x = rnd(1,e_max);
                s.push_back(x);
                w += x;
            }
            int add = coin() ? 1 : -1;
            if (e_max != 2) {
                if (w < 2*n) add = 1;
                if (w > (e_max-1)*n) add = -1;
            }
            while (w%n != 0) {
                int p = rnd(0,n-1);
                if (s[p]+add >= 1 && s[p]+add <= e_max) {
                    s[p] += add;
                    w += add;
                }
            }
            for (int i = 0; i < n; i++) {
                cout << s[i];
                cout << " \n"[i == n-1];
            }
        }
    }
    if (what == "max-small") {
        int e_max = atoi(argv[3]);
        int a = atoi(argv[4]);
        int b = atoi(argv[5]);
        for (int i = a; i <= b; i++) {
            create_max(i, {}, e_max);
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
    if (what == "max-small-possible") {
        int e_max = atoi(argv[3]);
        int a = atoi(argv[4]);
        int b = atoi(argv[5]);
        for (int i = a; i <= b; i++) {
            create_max(i, {}, e_max, true);
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
}
