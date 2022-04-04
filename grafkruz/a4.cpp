#include <bits/stdc++.h>

#define DP(x) cerr << #x << " = " << x << '\n';

using namespace std;

using ll = long long;

struct E {
    int n;
    int d;
};

struct V {
    int iter;
    int pred;
    int dist;
};

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<E>> scs{(unsigned int)n};
    for(auto& a : scs) {
        a.reserve(5);
    }

    vector<V> vs(n, {-1, -1, -1});

    for(int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        scs[a].push_back({b, w});
        scs[b].push_back({a, w});
    }

    int maxd = -1;
    int maxv[4] = {-1,-1,-1,-1};


    for(int i = 0; i < n; ++i) {
        for(E& sc : scs[i]) {
            for(E& ssc : scs[sc.n]) {
                if(vs[ssc.n].iter != i) {
                    vs[ssc.n] = {i, sc.n, sc.d + ssc.d};
                } else if(ssc.n == i) {
                    continue;
                } else if(vs[ssc.n].pred == sc.n) {
                    // mezi vrcholy max jedna hrana
                    continue;
                } else {
                    if(maxd < sc.d + ssc.d + vs[ssc.n].dist) {
                        maxd = sc.d + ssc.d + vs[ssc.n].dist;
                        maxv[0] = i;
                        maxv[1] = sc.n;
                        maxv[2] = ssc.n;
                        maxv[3] = vs[ssc.n].pred;
                        DP(i)
                        DP(sc.n)
                        DP(ssc.n)
                        DP(vs[ssc.n].pred)
                    }
                    if(sc.d + ssc.d > vs[ssc.n].dist) {
                        vs[ssc.n] = {i, sc.n, sc.d + ssc.d};
                    }
                }
            }
        }
    }

    cout << maxd << '\n';
    cout << maxv[0] << ' ' << maxv[1] << ' ' << maxv[2] << ' ' << maxv[3] << '\n';
}
