#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 500010;

int n, m, s, u, v;
int f[maxn][25],  dep[maxn], vis[maxn];

vector<int> g[maxn];

void dfs(int u, int fa) {
	f[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for (auto v : g[u])
		if (v != fa)
			dfs(v, u);
}

void init() {
	for (int j = 1; (1 << j) <= n; j++) //递推公式，往上跳2^j步 = 往上跳两次2^(j - 1)步
		for (int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j - 1]][j - 1];
}

int lca(int u, int v) {
	if (dep[u] < dep[v])
		swap(u, v);
	for (int i = 22; i >= 0; i--) //首先u跳到v的同一深度
		if (dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if (u == v)
		return u;
	for (int i = 22; i >= 0; i--) { //然后两个点一起往上跳
		if (f[u][i] != f[v][i]) {
			u = f[u][i];
			v = f[v][i];
		}
	}
	return f[u][0];
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> s;
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(s, 0);
	init();
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		cout << lca(u, v) << endl;
	}
	return 0;
}

/*
f[i][j]表示节点i往上跳2^j步达到的顶点，所以这里就是用倍增的方法大大加快向上查找的过程
*/
