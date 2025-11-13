#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 20010;

int n, m, u, v, idx, ans;
int dfn[maxn], low[maxn], isbridge[maxn];

vector<pair<int, int>> g[maxn];
vector<int> bridge;

void tarjan(int u, int fid) {
	dfn[u] = low[u] = ++idx;
	for (auto &[v, id] : g[u]) {
		if (!dfn[v]) {
			tarjan(v, id);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) //low[v] > dfn[u]，说明是割边
				isbridge[id] = 1;
		} else if (id != fid)
			low[u] = min(low[u], dfn[v]);
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) //dfn[i] == 0，说明是一个单独的连通快，进行dfs
			tarjan(i, 0);
	for (int i = 1; i <= m; i++) {
		if (isbridge[i]) {
			ans++;
			bridge.push_back(i);
		}
	}
	cout << ans << endl;
	for (auto id : bridge)
		cout << id << " ";
	return 0;
}

/*
割边与割点的大部分代码都相同，但有两个区别。首先需要更改的是判断条件。如果v通过返祖边可以到达u或u上面的顶点（比之前多了u节点本身，
因为割边只要求不经过id这条边，而不是不经过u这个点），说明(u, v)不是割边，此时有low[v] <= dfn[u]。反之，若low[v] > dfn[u]，
说明id这条边是割边。

并且，由于图中可能存在重边，所以dfs中记录的不能只是父亲节点fa，而是记录父亲边的编号fid，这样就可以把fid和(u, fa)之前的其他重边区分开来。
*/
