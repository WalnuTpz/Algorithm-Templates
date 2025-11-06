#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;

int n, m, u, v, w, color[maxn], flag;

vector<pair<int, int>> g[maxn];

void dfs(int u, int c) {
	if (!flag)
		return;
	color[u] = c;
	for (auto &[v, w] : g[u]) {
		if (color[v] == 0)
			dfs(v, 3 - c);
		else if (color[v] == c) { //邻居与自己的颜色相同，则不是二分图
			flag = 0;
			return;
		}
	}
}

int main() {
	flag = 1;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	for (int i = 1; i <= n; i++)
		if (color[i] == 0)
			dfs(i, 1);
	if (flag)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	return 0;
}
