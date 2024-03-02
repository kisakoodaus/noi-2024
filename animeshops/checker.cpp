#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
    auto p = read_ints(3, 0, 2e5);
    int n = p[0];
    int m = p[1];
    int h = p[2];

    bool line = m == n-1;

    if (n < 1 || n > 1e5 || h < 1 || h > n) fail();

    set<int> hs;
    for (auto x : read_ints(h, 1, n)) {
        if (hs.count(x)) fail();
        hs.insert(x);
    }

    set<pair<int,int>> e;
    for (int i = 1; i <= m; i++) {
        auto r = read_ints(2, 1, n);
        if (r[0] == r[1]) fail();
        if (abs(r[0]-r[1]) != 1) line = false;
        if (e.count({r[0],r[1]}) || e.count({r[1],r[0]})) fail();
        e.insert({r[0],r[1]});
    }

    vector<int> g;
    if (n <= 1000 && m <= 2000) g.push_back(1);
    if (line) g.push_back(2);
    if (n <= 1e5 && m <= 2e5) g.push_back(3);

    end_groups(g);
}
