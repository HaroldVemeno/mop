#include <bits/stdc++.h>

#define D(x) cerr << #x << ": " << (x) << '\n';

using ll = long long;
using namespace std;

constexpr int N = 10000;

struct E {
    int s;
    int m;

    friend ostream& operator <<(ostream& o, const E& a) {
        o << "(sum: " << a.s << ", max: " << a.m << ")";
        return o;
    }
};

struct LE {
    int s;
    int m;
    int la;
    bool nlf;

    friend ostream& operator <<(ostream& o, const LE& a) {
        o << "(sum: " << a.s << ", max: " << a.m << ", lazy add: " << a.la << ", nullified: " << boolalpha << a.nlf << ")";
        return o;
    }
};

int d;
int l;
int n;
LE u[4*N];

void build() {
    for(int i = n-1; i > 0; --i) {
        LE a = u[2*i];
        LE b = u[2*i + 1];
        u[i] = {a.s + b.s, max(a.m, b.m), 0, false};
    } 
}



E traverse(int f, int t, int a = 0, bool nlf = false, int lu = 0, int ru = n, int ui = 1) {
    int rru = min(l, ru);
    int len = rru - lu;
    if(rru <= f || t <= lu || t < f) return {0, 0};
    if(f <= lu && rru <= t) {
        if(nlf) {
            u[ui].nlf = true;
            u[ui].la = 0;
            u[ui].s = 0;
            u[ui].m = 0;
        }

        u[ui].la += a;
        u[ui].s += a * len;
        u[ui].m += a;
        return {u[ui].s, u[ui].m};
    }

    if(u[ui].nlf) {
        u[ui*2  ].nlf = true;
        u[ui*2  ].s = 0;
        u[ui*2  ].m = 0;
        u[ui*2  ].la = 0;

        u[ui*2+1].nlf = true;
        u[ui*2+1].s = 0;
        u[ui*2+1].m = 0;
        u[ui*2+1].la = 0;

        u[ui].nlf = false;
    }

    int off = max(0, ru - l);

    u[ui*2  ].m += u[ui].la;
    u[ui*2  ].la += u[ui].la;
    u[ui*2  ].s += u[ui].la * len/2;

    u[ui*2+1].m += u[ui].la;
    u[ui*2+1].la += u[ui].la;
    u[ui*2+1].s += u[ui].la * (len/2 - off);

    u[ui].la = 0;

    E l = traverse(f, t, a, nlf, lu, (lu+ru)/2, ui*2);
    E r = traverse(f, t, a, nlf, (lu+ru)/2, ru, ui*2+1);

    u[ui].s = u[ui*2].s + u[ui*2+1].s;
    u[ui].m = max(u[ui*2].m, u[ui*2+1].m);

    return {l.s+r.s, max(l.m, r.m)};
}

void setin(int f, int t, int a) {
    traverse(f, t, a, true);
}
void nullifyin(int f, int t) {
    traverse(f, t, 0, true);
}
void addin(int f, int t, int a) {
    traverse(f, t, a);
}
E queryin(int f, int t) {
    return traverse(f, t);
}

int digits(int a) {
    int i;
    for(i = 0; 1 << i < a; ++i);
    return i;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> l;

    d = digits(l);
    n = 1 << d;

    // for(int i = 0; i < l; ++i) {
    //     int t;
    //     cin >> t;
    //     u[n+i] = {t,t,0};
    // }

    for(int i = 0; i < n; ++i) {
        u[n+i] = {0, 0, 0, false};
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
                cin >> f >> t;
                cout << queryin(f, t) << '\n';
            break;case 2:
                cout << "add> " << flush;
                cin >> f >> t >> a;
                addin(f, t, a);
            break;case 3:
                cout << "nullify> " << flush;
                cin >> f >> t;
                nullifyin(f, t);
            break;case 4:
                cout << "sums:\n";
                j = 2;
                for(int i = 1; i < 2*n; ++i)  {
                    if(i == j) {
                        cout << '\n';
                        j *= 2;
                    }
                    cout << u[i].s << ' ';
                }
                cout << '\n';
            break;case 5:
                cout << "maxs:\n";
                j = 2;
                for(int i = 1; i < 2*n; ++i)  {
                    if(i == j) {
                        cout << '\n';
                        j *= 2;
                    }
                    cout << u[i].m << ' ';
                }
                cout << '\n';
            break;case 6:
                cout << "lazy adds:\n";
                j = 2;
                for(int i = 1; i < 2*n; ++i)  {
                    if(i == j) {
                        cout << '\n';
                        j *= 2;
                    }
                    cout << u[i].la << ' ';
                }
                cout << '\n';
            break;case 7:
                cout << "nullified:\n" << noboolalpha;
                j = 2;
                for(int i = 1; i < 2*n; ++i)  {
                    if(i == j) {
                        cout << '\n';
                        j *= 2;
                    }
                    cout << u[i].nlf << ' ';
                }
                cout << '\n';
        }


    }

}
