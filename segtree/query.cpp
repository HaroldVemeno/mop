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

int l;
int n;
E u[4*N];

void build() {
    for(int i = n-1; i > 0; --i) {
        E a = u[2*i];
        E b = u[2*i + 1];
        u[i] = {a.s + b.s, max(a.m, b.m)};
    }
}

E getallup(int f, int t) {
    f += n;
    t += n + 1;

    int s = 0;
    int m = 0;

    while(f != t) {
        if(f % 2 == 1) {
            s += u[f].s;
            m = max(u[f].m, m);
            ++f;
        }
        if(t % 2 == 1) {
            s += u[t-1].s;
            m = max(u[t-1].m, m);
            --t;
        }

        f /= 2;
        t /= 2;
    }

    return {s, m};
}

E getalldown(int f, int t, int lu = 0, int ru = n, int ui = 1) {

    if(f >= ru || t < lu) return {0, 0};

    if(f == lu && t == ru-1) {
        return {u[ui].s, u[ui].m};
    }

    E l = getalldown(f, t, ru, (ru+lu)/2, ui*2);
    E r = getalldown(f, t, (ru+lu)/2, ui*2+1);

    return {l.s + r.s, max(r.m, l.m)};
}

void addto(int i, int a) {
    i += n;
    int m = u[i].m + a;
    while(i >= 1) {
        u[i].s += a;
        u[i].m = max(u[i].m, m);
        i /= 2;
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
        u[n+i] = {0,0};
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
                cout << getall(f, t) << '\n';
            break;case 2:
                cout << "add> " << flush;
                cin >> f >> a;
                addto(f, a);
            break;case 3:
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
            break;case 4:
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
        }
    }
}
