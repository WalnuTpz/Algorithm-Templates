#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 200010;

int n, u, v, dp1[maxn], dp2[maxn], ans;

vector<pair<int, int>> g[maxn];

void dfs(int u, int fa) {
	dp1[u] = dp2[u] = 0;
	for (auto &[v, w] : g[u]) {
		if (v == fa)
			continue;
		dfs(v, u);
		int dv = dp1[v] + w;
		if (dv > dp1[u]) { //对于每个v，最多更新dp1, dp2中的一个值，因此它们对应的路径中经过的就是u的不同的儿子
			dp2[u] = dp1[u];
			dp1[u] = dv;
		} else if (dv > dp2[u])
			dp2[u] = dv;
	}
	ans = max(d, dp1[u] + dp2[u]);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}

/*
树上任意两节点之间最长的简单路径即为树的直径，并且一棵树可以有多条直径

可以用两次dfs或树形dp的方法求出树的直径长度，并也可以通过记录前一个节点的方法求出具体直径。这里讲树形dp的方法，首先以1为根进行dfs，
设dp1[u]为u出发的最长路径长度，dp2[u]为u出发的第二长的路径长度，并且它们没有公共边（也就是这两条路径经过的是u的不同的儿子），
那么(dp1[u] + dp2[u])就表示经过u的最长路径长度，将所有点的这个值取max即为树的直径

这种方法是可以处理边长为负数的情况的
*/
