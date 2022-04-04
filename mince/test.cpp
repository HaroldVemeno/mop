#include <bits/stdc++.h>

#define DP(x) cerr << #x << " = " << x << '\n';

using namespace std;

using ll = long long;

struct Cboth {
    template<typename T>
    friend Cboth& operator <<(Cboth& c, const T& t) {
        cout << t;
        cerr << t;
        return c;
    }
} cboth;


int main() {
    ll n = 12, g = 1000000000000000000;
    cout << n << ' ' << g << '\n';

    srand(time(nullptr));

    for(int i = 0; i < n; ++i) {
        cout << rand()%1000 + 200 << ' ';
    }
    cout << '\n';

    return 0;
}
