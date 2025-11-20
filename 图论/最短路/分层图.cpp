#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll, ll>;
const int maxn = 1000010, inf = 2147483647;

int n, m, k, s, t, u, v, w, vis[maxn];
ll dis[maxn];

vector<pii> g[maxn];
priority_queue<pii, vector<pii>, greater<pii>> pq;

void dijkstra(int s) {
	dis[s] = 0;
	pq.push({0, s});
	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (auto [v, w] : g[u]) {
			if (vis[v])
				continue;
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				pq.push({dis[v], v});
			}
		}
	}
}

int main() {
	cin >> n >> m >> k;
	cin >> s >> t;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
		for (int j = 1; j <= k; j++) {
			g[u + (j - 1) * n].push_back({v + j * n, 0});
			g[v + (j - 1) * n].push_back({u + j * n, 0});
			g[u + j * n].push_back({v + j * n, w});
			g[v + j * n].push_back({u + j * n, w});
		}
	}
	for (int j = 1; j <= k; j++)
		g[s + (j - 1) * n].push_back({s + j * n, 0});
	for (int i = 0; i <= n * (k + 1); i++)
		dis[i] = inf;
	dijkstra(s);
	cout << dis[t + k * n] << endl;
	return 0;
}

/*
对于题目中的k次免费机会，我们可以额外建k层图，总共(k + 1)层，对这个大图进行最短路的求解，最终答案就是第(k + 1)层对应的终点的最短路长度。
首先每层中的节点和正常连边，然后对于图中的所有边(u, v)，它的两个顶点在第i层对应的节点为(u + n * (i - 1)),(v + n * (i - 1))，
然后在1~k层中分别将u对应的节点往下一层中v对应的节点连一条长为0的边，如果走了这条边就代表使用一次免费机会，同时进入了下一层图
（也就是免费机会减少了一次）。但还有一点需要注意的是，需要在起点在每层中的对应节点也连一条长度为0的边，这样就可以模拟一些使用
免费机会少于k次的极端情况。
*/
