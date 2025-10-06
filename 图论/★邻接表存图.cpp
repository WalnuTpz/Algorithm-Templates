#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
int n, m, u, v, w;

struct edge { //不用结构体也可以用pair<int, int>
	int to, dis;
};
vector<edge> g[N];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		g[u].push_back((edge) {
			u, w
		});
	}

	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].to, w = g[u][i].dis;
		//遍历
	}
	return 0;
}
