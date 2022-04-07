// O(m+k) - bez komprese souradnic/pole misto map
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = int64_t;
#define rep(i, a, n) for (int i = a; i < (int)(n); i++)
#define per(i, a, n) for (int i = (n)-1; i >= (int)(a); i--)
template <typename T, typename U>
ostream& operator<<(ostream& _s, pair<T, U> _t) {
    _s << "(" << _t.first << "," << _t.second << ")";
    return _s;
}
template <typename T, typename U>
istream& operator>>(istream& _s, pair<T, U>& _t) {
    _s >> _t.first >> _t.second;
    return _s;
}
template <typename T>
ostream& operator<<(ostream& _s, vector<T> _t) {
    rep(i, 0, _t.size()) _s << (i ? " " : "") << _t[i];
    return _s;
}
template <typename T>
istream& operator>>(istream& _s, vector<T>& _t) {
    rep(i, 0, _t.size()) _s >> _t[i];
    return _s;
}
template <typename T>
ostream& operator<<(ostream& _s, vector<vector<T>> _t) {
    rep(i, 0, _t.size()) { _s << i << ": " << _t[i] << endl; }
    return _s;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;

    if (m > 1e6) {
        return 0;
    }
    vector<int> events(m + 1, 0);

    rep(i, 0, k) {
        int s, o, d;
        cin >> s >> o >> d;
        int t1 = o - s;
        int t2 = d - s;

        t1 = max(t1, 0);
        t2 = min(t2, m - 1);
        if (t1 <= t2) {
            events[t1]++;
            events[t2 + 1]--;
        }
    }

    int best = 0;
    int cur = 0;

    rep(i, 0, m + 1) {
        cur += events[i];
        best = max(best, cur);
    }

    assert(cur == 0);

    cout << best << endl;
}
