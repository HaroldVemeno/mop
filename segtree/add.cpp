#include <bits/stdc++.h>

#define D(x) cerr << #x << ": " << (x) << '\n';

using ll = long long;
using namespace std;

constexpr int N = 10000;


int l;
int n;
int u[4*N];

void build() {
    for(int i = n-1; i > 0; --i) {
        u[i] = 0;
    }
}

int getone(int i) {
    i += n;

    int s = 0;

    while(i >= 1) {
        s += u[i];
        i /= 2;
    }

    return s;
}

void addintdown(int f, int t, int a, int lu = 0, int ru = n, int ui = 1) {
    if(ru <= f || t <= lu) return;
    if(f == lu && t == ru - 1) {
        u[ui] += a;
    }

    addintdown(f, t, a, lu, (lu+ru)/2, ui*2);
    addintdown(f, t, a, (lu+ru)/2, ru, ui*2+1);
}

void addint(int f, int t, int a) {
    f += n;
    t += n+1;

    while(f != t) {

        if(f&1) u[f++] += a;
        if(t&1) u[--t] += a;

        f /= 2;
        t /= 2;
    }
}

int biggerbit(int a) {
    int i;
    for(i = 1; i < a; i <<= 1);
    return i;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> l;

    n = biggerbit(l);

    // for(int i = 0; i < l; ++i) {
    //     int t;
    //     cin >> t;
    //     u[n+i] = {t,t,0};
    // }

    for(int i = 0; i < n; ++i) {
        u[n+i] = 0;
    }

    build();

    while(true) {
        cout << "> " << flush;
        int q;
        cin >> q;
        int f, t, a, j;
        switch(q) {
            break;case 0:
                return 0;
            break;case 1:
                cout << "get> " << flush;
                cin >> f;
                cout << getone(f) << '\n';
            break;case 2:
                cout << "add> " << flush;
                cin >> f >> t >> a;
                addint(f, t, a);
            break;case 3:
                cout << "values:\n";
                j = 2;
                for(int i = 1; i < 2*n; ++i)  {
                    if(i == j) {
                        cout << '\n';
                        j *= 2;
                    }
                    cout << u[i] << ' ';
                }
                cout << '\n';
        }
    }
}
