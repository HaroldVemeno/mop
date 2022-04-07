#include <bits/stdc++.h>

#define REP(i, n) for(int i = 0; i < n; ++i)

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

int n, m, k;

vector<ii> intervals;

int main(){
	cin >> n >> m >> k;

	int s, o, d;

	REP(i, k){
		cin >> s >> o >> d;
		if(o-s >= m){
			// cerr << "Nezastihnutelny majitel stanku" << endl;
			continue;
		}
		intervals.push_back({max(o-s,0), 1});
		intervals.push_back({min(d-s+1,m), -1});
	}

	// nejdriv zavre, pak otevre
	sort(intervals.begin(), intervals.end());

	int mx = 0;
	int cur = 0;

	for(auto x : intervals){
		cur += x.second;
		//if(cur > mx) cerr << "New max " << cur << " at " << x.first << endl;
		mx = max(mx,cur);
	}

	cout << mx << endl;

}