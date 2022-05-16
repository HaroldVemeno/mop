#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define D(x) cerr << #x << ": " << (x) << '\n';

int get_value(int);

int compute_maximum(int e) {
    int b = 0;
    while(true) {
        int m = (b+e)/2;
        D(b)
        D(e)
        D(m)
        if(e - b == 1) {
            return get_value(b);
        }
        if(e - b == 2) {
            return max(get_value(b), get_value(b+1));
        }
        int r = get_value(m-1);
        int s = get_value(m);
        if(r == s) return r;
        if(r < s) {
            b = m;
        } else {
            e = m;
        }

    }
}
