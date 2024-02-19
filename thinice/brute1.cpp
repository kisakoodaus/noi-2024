#include <iostream>
#include <set>
#include <array>
 
using namespace std;
 
int n, m;
int d[1111][1111];
 
int coins;
set<array<int,3>> seen;
 
int r;
 
void search(int y, int x, int c) {
    if (y < 1 || x < 1 || y > n || x > m || c > d[y][x]) return;
 
    if (y == 1 || x == 1 || y == n || x == m) {
        r = max(r,c);
    }
 
    if (seen.count({y,x,coins})) return;
    seen.insert({y,x,coins});
 
    search(y+1, x, c);
    search(y-1, x, c);
    search(y, x+1, c);
    search(y, x-1, c);
 
    int mask = 1 << (y*5+x);
    if (!(coins&mask)) {
        coins ^= mask;
        search(y, x, c+1);
        coins ^= mask;
    }
}
 
 
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> d[i][j];
        }
    }
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 || j == 1 || i == n || j == m) search(i,j,0);
        }
    }
 
    cout << r << "\n";
}
