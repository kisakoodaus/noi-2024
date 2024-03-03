#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
    int t = read_int(1,1000);

    bool s1 = true;
    bool s2 = true;
    bool s7 = true;

    int e_max = 0;

    for (int i = 1; i <= t; i++) {
        int n = read_int(1,100);
        auto v = read_ints(n,1,n);

        if (n > 8) s1 = false;
        if (n > 16) s7 = false;

        set<int> z;
        for (auto x : v) {
            if (z.count(x)) s2 = false;
            z.insert(x);
        }

        for (auto x : v) e_max = max(e_max, (int)x);
    }

    vector<int> groups;
    if (s1) groups.push_back(1);
    if (s2) groups.push_back(2);
    if (e_max <= 2) groups.push_back(3);
    if (e_max <= 3) groups.push_back(4);
    if (e_max <= 4) groups.push_back(5);
    if (e_max <= 5) groups.push_back(6);
    if (s7) groups.push_back(7);
    groups.push_back(8);

    end_groups(groups);
}
