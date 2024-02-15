#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Give numerical grade to the user
[[noreturn]] void grade(int result)
{
    cout << "1\n"
         << result << '\n';
    exit(0);
}
// Indicate that program failed to produce the right answer
[[noreturn]] void fail()
{
    cout << "0\n";
    exit(0);
}
// Indicate that the submission was accepted
[[noreturn]] void accept()
{
    cout << "1\n";
    exit(0);
}
#define SAFE_READ(x) \
    do               \
    {                \
        if (!(x))    \
            fail();  \
    } while (false)

int main(int argc, char **argv)
{
    string x1 = argv[1]; // correct output
    string x2 = argv[2]; // user output
    string x3 = argv[3]; // input
    ifstream correct, user, input;
    correct.open(x1);
    user.open(x2);
    input.open(x3);

    int t;
    input >> t;

    while (t--) {
        int n;
        input >> n;
        vector<int> s(n);
        for (int i = 0; i < n; i++) input >> s[i];

        string v1, v2;
        correct >> v1;
        user >> v2;
        if (v1 != v2) fail();
        if (v1 == "NO") continue;

        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            user >> p[i];
        }

        map<int,int> m1, m2;
        for (int i = 0; i < n; i++) {
            m1[s[i]]++;
            m2[p[i]]++;
        }
        if (m1 != m2) fail();

        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            int u = (i+s[i])%n;
            if (c[u]) fail();
            c[u] = 1;
        }
    }

    accept();
}
