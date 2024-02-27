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

    if (n < 1 || n > 1e5 || h > n) fail();

    set<int> hs;
    for (auto x : read_ints(h, 1, n)) {
        if (hs.count(x)) fail();
        hs.insert(x);
    }

    for (int i = 1; i <= m; i++) {
        auto r = read_ints(2, 1, n);
        if (r[0] == r[1]) fail();
    }

    vector<int> g;
    if (n <= 100 && m <= 200) g.push_back(1);
    if (n <= 2000 && m <= 5000) g.push_back(2);
    if (n <= 1e5 && m <= 2e5) g.push_back(3);

    end_groups(g);
}
