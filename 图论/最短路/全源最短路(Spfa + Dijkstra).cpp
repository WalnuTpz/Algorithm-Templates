#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
using pii = pair<ll, ll>;
const int maxn = 3010;
const ll inf = 1e9;

int n, m, u, v, w, vis[maxn], num[maxn];
ll h[maxn], dis[maxn], ans;

vector<pii> g[maxn];

int spfa(int s) {
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		h[i] = inf;
		vis[i] = 0;
	}
	h[s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		vis[u] = 0;
		for (auto &[v, w] : g[u]) {
			if (h[u] + w < h[v]) {
				h[v] = h[u] + w;
				num[v] = num[u] + 1;
				if (num[v] == n + 1)
					return 0;
				if (!vis[v]) {
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
	return 1;
}

void dijkstra(int s) {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	for (int i = 1; i <= n; i++) {
		dis[i] = inf;
		vis[i] = 0;
	}
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
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		g[0].push_back({i, 0});
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		g[u].push_back({v, w});
	}
	if (!spfa(0)) {
		cout << -1 << endl;
		return 0;
	}
	for (int u = 1; u <= n; u++)
		for (auto &[v, w] : g[u])
			w += h[u] - h[v];
	for (int i = 1; i <= n; i++) {
		dijkstra(i);
		for (int j = 1; j <= n; j++) {
			if (dis[j] == inf)
				cout << -1 << " ";
			else
				cout << dis[j] - h[i] + h[j] << " ";
		}
		cout << endl;
	}
	return 0;
}

/*
对于求出图中所有点之间的最短路的问题，可以使用floyd或n次spfa，但是这个会比较慢。所以考虑使用n次dijkstra，但此时无法处理负环，
所以需要将所有边的权值变成正的。

朴素的想法是把所有边的权值都加上一个大正数，最后再减去这些大正数，但这样会破坏最短路（因为可能有的路径
由于边数较少，加的大正数也少，被误认为最短路，但实际上它并不是最短路）。

这里我们考虑添加一个超级源点0，并与所有点连一条边长为0的边，并用spfa求出它到每个点的最短路h[i]，所以此时有h[u] + w(u, v) >= h[v]，
所以令w'(u, v) = w(u, v) + h[u] - h[v] >= 0，这就是新的边权。然后考虑此时求出的最短路i -> p1 -> p2 ... pk -> j，则dis'(i, j) =
w'(i, p1) + w'(p1, p2) ... + w'(pk, j) = w(i, p1) + (h[i] - h[p1]) + w(p1, p2) + (h[p1] - h[p2]) ... + w(pk, j) + (h[pk] - h[j])
= w(i, p1) + w(p1, p2) ... + w(pk, j) + (h[i] - h[j]) = dis(i, j) + (h[i] - h[j])。所以真实的dis(i, j)就是dis'(i, j) - (h[i] - h[j])
*/
