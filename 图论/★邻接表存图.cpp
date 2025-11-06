#include <bits/stdc++.h>
using namespace std;

const int maxn = 10010;

int n, m, u, v, w;

vector<pair<int, int>> g[maxn]; //除了pair也可以使用struct

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		g[u].push_back({v, w});
	}

	for (auto &[v, w] : g[u]) {
		//遍历
	}
	return 0;
}
