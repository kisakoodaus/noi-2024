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
    bool s3 = true;
    bool s4 = true;

    for (int i = 1; i <= t; i++) {
        int n = read_int(1,100);
        auto v = read_ints(n,1,n);

        if (n > 8) s1 = false;
        if (n > 16) s2 = false;

        set<int> z;
        for (auto x : v) {
            if (z.count(x)) s3 = false;
            z.insert(x);
        }

        for (auto x : v) if (x > 5) s4 = false;
    }

    vector<int> groups;
    if (s1) groups.push_back(1);
    if (s2) groups.push_back(2);
    if (s3) groups.push_back(3);
    if (s4) groups.push_back(4);
    groups.push_back(5);

    end_groups(groups);
}
