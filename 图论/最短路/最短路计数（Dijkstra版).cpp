#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
using pii = pair<ll, ll>;
const int maxn = 1000010, inf = 2147483647, mod = 100003;

int n, m, cnt, u, v, w, vis[maxn];
ll dis[maxn], ans[maxn]; //ans[i]表示1-i的最短路条数

vector<int> g[maxn];
priority_queue<pii, vector<pii>, greater<pii>> pq;

void dijkstra(int s) {
	dis[s] = 0;
	pq.push({0, s});
	ans[s] = 1;
	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (auto v : g[u]) {
			//if(vis[v]) continue;
			//正常dijk中的这一句要去掉，因为正常dijk里每个点只需要在第一次找到最短路时进入队列，但这道题里可能会有多条等长的最短路
			//如果不去掉这一句，那些一样短的路径就会被跳过，它们就无法累加到答案里了
			if (dis[u] + 1 < dis[v]) { //找到更短的路径
				dis[v] = dis[u] + 1;
				ans[v] = ans[u]; //1-v的最短路条数等于1-u的最短路条数
				pq.push({dis[v], v});
			} else if (dis[u] + 1 == dis[v]) //找到一样短的路径
				ans[v] = (ans[v] + ans[u]) % mod; //1-v的最短路条数需要加上1-u的最短路条数
		}
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		dis[i] = inf;
	dijkstra(1);
	for (int i = 1; i <= n; i++)
		cout << ans[i] % mod << endl;
	return 0;
}

