#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 5010, inf = 2e9;

int n, m, u, v, w, vis[maxn], num[maxn], flag;
long long dis[maxn];

vector<pair<int, int>> g[maxn];

int spfa(int s) {
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
				num[v] = num[u] + 1;
				if (num[v] >= n + 1)
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

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> v >> u >> w; //xv - xu <= w
		g[u].push_back({v, w});
	}
	for (int i = 1; i <= n; i++) {
		dis[i] = inf;
		g[0].push_back({i, 0});
	}
	flag = spfa(0);
	if (flag) {
		for (int i = 1; i <= n; i++)
			cout << dis[i] << " ";
		cout << endl;
	} else
		cout << "NO" << endl;
	return 0;
}

/*
有n个变量x1, x2...xn，有m组不等式x_ci - x_c'i <= yi，求这个不等式组的一组可行解

把不等式x_ci - x_c'i <= yi看成x_ci <= x_c'i + yi，然后可以发现新不等式和最短路里的松弛操作很像，所以这道题可以转化为最短路来解决。
首先把每个变量xi对应一个顶点，并假设一个虚拟源点x0，将它与所有点之间连一条长为0的边，然后对于所有xv - xu <= w，在(u, v)之间
连接一条长为k的有向边。那么如果xi的值表示x0到顶点i的最短路，那么xv - xu <= w就符合松弛操作xv <= xu + w，也就是原不等式的变形。
然后用spfa求解即可

对于有解的情况，求出的最短路dis[i]就是xi的一个解
对于无解的情况，注意因为添加了一个虚拟源点，所以判断出现负环的时候是num[v] >= n + 1而不是num[v] >= n
*/
