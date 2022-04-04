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
  int ppred;
  int pred;
  int dist;

  friend bool operator<(const V &a, const V &b) {
      return a.dist < b.dist;
  }
};

int main() {
  cin.sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<E>> scs{(unsigned int)n};
  for (auto &a : scs) {
    a.reserve(5);
  }

  vector<array<V, 5>> vs{};
  vs.reserve(n);
  for (int i = 0; i < n; ++i) {
    array<V, 5> v{};
    v[0] = {-1, -1, -1, -1};
    v[1] = {-1, -1, -1, -1};
    v[2] = {-1, -1, -1, -1};
    v[3] = {-1, -1, -1, -1};
    v[4] = {-1, -1, -1, -1};
    vs.push_back(v);
  }

  for (int i = 0; i < m; ++i) {
    int a, b, w;
    cin >> a >> b >> w;
    scs[a].push_back({b, w});
    scs[b].push_back({a, w});
  }

  // for (int i = 0; i < n; ++i) {
  //     sort(begin(scs[i]), end(scs[i]), [](const E a, const E b){return a.d >
  //     b.d;});
  // }

  int maxd = -1;
  int maxv[6] = {-1, -1, -1, -1, -1, -1};

  for (int i = 0; i < n; ++i) {
    for (E &sc : scs[i]) {
      if (sc.n < i)
        continue;
      for (E &ssc : scs[sc.n]) {
        if (ssc.n < i)
          continue;
        if (i == ssc.n)
          continue;
        for (E &sssc : scs[ssc.n]) {
          if (i == sssc.n)
            continue;
          if (sc.n == sssc.n)
            continue;
          int dd = sc.d + ssc.d + sssc.d;
          auto &others = vs[sssc.n];
          for (auto &other : others) {
            if (other.iter != i) {
              break;
            } else if (other.ppred == sc.n || other.pred == sc.n ||
                       other.ppred == ssc.n || other.pred == ssc.n) {
              continue;
            } else if (maxd < dd + other.dist) {
              maxd = dd + other.dist;
              maxv[0] = i;
              maxv[1] = sc.n;
              maxv[2] = ssc.n;
              maxv[3] = sssc.n;
              maxv[4] = other.pred;
              maxv[5] = other.ppred;
              DP(i)
              DP(sc.n)
              DP(ssc.n)
              DP(sssc.n)
              DP(other.pred)
              DP(other.ppred)
            }
          }

          auto overlap = [](int a, int b, V o) {
            bool r = false;
            for (int x : {a, b})
              for (int y : {o.pred, o.ppred})
                r = r || x == y;
            return r;
          };

          for (int j = 0; j < 5; ++i) {
            if (others[j].iter != i) {
              others[j] = {i, sc.n, ssc.n, dd};
              goto end;
            } else if (dd > others[j].dist && others[j].pred == sc.n &&
                       others[j].ppred == ssc.n) {
              others[j] = {i, sc.n, ssc.n, dd};
              goto end;
            }
          }
          if (indep(sc.n, ssc.n, others)) {
            *min_element(begin(others), end(others)) = {i, sc.n, ssc.n, dd};
            goto end;
          }

        // auto test = [&](int a){
        //     int b = (a + 1) % 3;
        //     int c = (a + 2) % 3;
        //     bool r = false;
        //     for(auto x : {sc.n, ssc.n})
        //     for(auto y : {others[b].pred, others[b].ppred})
        //     for(auto z : {others[c].pred, others[c].ppred})
        //         r = r || (y == x && z == x);
        //     return !r;
        // };

        // if (other3[0].iter != i) {
        //   other3[0] = {i, sc.n, ssc.n, dd};
        // } else if (dd > other3[0].dist && other3[0].pred == sc.n &&
        // other3[0].ppred == ssc.n) {
        //   other3[0] = {i, sc.n, ssc.n, dd};
        // } else if (other3[1].iter != i) {
        //   other3[1] = {i, sc.n, ssc.n, dd};
        // } else if (dd > other3[1].dist && other3[1].pred == sc.n &&
        // other3[1].ppred == ssc.n) {
        //   other3[1] = {i, sc.n, ssc.n, dd};
        // } else if (other3[2].iter != i) {
        //   other3[2] = {i, sc.n, ssc.n, dd};
        // } else if (dd > other3[2].dist && other3[2].pred == sc.n &&
        // other3[2].ppred == ssc.n) {
        //   other3[2] = {i, sc.n, ssc.n, dd};
        // } else if (other3[0].dist <= other3[1].dist && other3[0].dist <=
        // other3[2].dist && dd > other3[0].dist && test(0)) {
        //   other3[0] = {i, sc.n, ssc.n, dd};
        // } else if (other3[1].dist <= other3[2].dist && dd > other3[1].dist &&
        // test(1)) {
        //   other3[1] = {i, sc.n, ssc.n, dd};
        // } else if (dd > other3[2].dist && test(2)) {
        //   other3[2] = {i, sc.n, ssc.n, dd};
        // }
        //
        end:
        }
      }
    }
  }

  cout << maxd << '\n';
  cout << maxv[0] << ' ' << maxv[1] << ' ' << maxv[2] << ' ' << maxv[3] << ' '
       << maxv[4] << ' ' << maxv[5] << '\n';
}
