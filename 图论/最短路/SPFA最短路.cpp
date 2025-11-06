#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010, INF = 2e9;
int n, m, s, u, v, w, vis[maxn], num[maxn], flag;
long long dis[maxn];

vector<pair<int, int>> g[maxn];

int spfa(int s) { //求起点s到每个点的最短路
	queue<int> q;
	dis[s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		vis[u] = 0;
		for (auto &[v, w] : g[u]) {
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				num[v] = num[u] + 1; //num数组表示最短路径经过几条边
				if (num[v] >= n)
					return 0;
				// 在不经过负环的情况下，最短路至多经过 n - 1 条边
				// 因此如果经过了多于 n 条边，一定说明经过了负环
				if (!vis[v]) {
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
	return 1;
}

int main() {
	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		g[u].push_back({v, w});
	}
	for (int i = 1; i <= n; i++)
		dis[i] = INF;
	flag = spfa(s);
	if (flag)
		for (int i = 1; i <= n; i++)
			cout << dis[i] << " ";
	else
		cout << "-1" << endl; //存在负环
	return 0;
}

/*
Bellman–Ford / spfa过程：
	先介绍 Bellman–Ford 算法要用到的松弛操作（Dijkstra 算法也会用到松弛操作）
	对于边 (u,v)，松弛操作对应下面的式子：dis[v] = min(dis[v], dis[u] + w(u, v))
	这么做的含义是显然的：我们尝试用 S -> u -> v（其中 S -> u 的路径取最短路）
这条路径去更新 v 点最短路的长度，如果这条路径更优，就进行更新。
	Bellman–Ford 算法所做的，就是不断尝试对图上每一条边进行松弛。我们每进行一轮循环，
就对图上所有的边都尝试进行一次松弛操作，当一次循环中没有成功的松弛操作时，算法停止。
	每次循环是 O(m) 的，那么最多会循环多少次呢？
	在最短路存在的情况下，由于一次松弛操作会使最短路的边数至少 +1，而最短路的边数最多为 n-1，
因此整个算法最多执行 n-1 轮松弛操作。故总时间复杂度为 O(nm)。
	但还有一种情况，如果从 S 点出发，抵达一个负环时，松弛操作会无休止地进行下去。
注意到前面的论证中已经说明了，对于最短路存在的图，松弛操作最多只会执行 n-1 轮，
因此如果第 n 轮循环时仍然存在能松弛的边，说明从 S 点出发，能够抵达一个负环。

队列优化：SPFA
	即 Shortest Path Faster Algorithm。
	很多时候我们并不需要那么多无用的松弛操作。
	很显然，只有上一次被松弛的结点，所连接的边，才有可能引起下一次的松弛操作。
	那么我们用队列来维护「哪些结点可能会引起松弛操作」，就能只访问必要的边了。
	SPFA 也可以用于判断 s 点是否能抵达一个负环，只需记录最短路经过了多少条边，当经过了至少 n 条边时，
说明 s 点可以抵达一个负环。
	虽然在大多数情况下 SPFA 跑得很快，但其最坏情况下的时间复杂度为 O(nm)，将其卡到这个复杂度也是不难的，
所以考试时要谨慎使用（在没有负权边时最好使用 Dijkstra 算法，在有负权边且题目中的图没有特殊性质时，
若 SPFA 是标算的一部分，题目不应当给出 Bellman–Ford 算法无法通过的数据范围）。
*/