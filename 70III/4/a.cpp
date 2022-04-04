#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> sl(n);
    vector<vector<int>> pl(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        sl[u].push_back(v);
        pl[v].push_back(u);
    }

    int e = 0;

    vector<bool> seen;

    stack<int> st;

    for(int i = 0; i < n; ++i) {
        int r = i;
        if(seen[i]) continue;
        st.push(i);
        while(!st.empty()) {
            int r = st.top();
            st.pop();
            if(seen[r]) continue;
            for(auto a : sl[r]) {
                if(seen[a])
            }
        }

    }


}
