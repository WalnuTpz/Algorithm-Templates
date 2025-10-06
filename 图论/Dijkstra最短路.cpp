#include <bits/stdc++.h>
using namespace std;
const int N = 10010, M = 500010, INF = 2147483647;
int n, m, s, cnt, u, v, w, head[N], vis[N];
long long  dis[N];

struct Edge {
	int to;
	int dis;
	int nxt;
} edge[M];

void add_edge(int from, int to, int dis) {
	cnt++;
	edge[cnt].to = to;
	edge[cnt].dis = dis;
	edge[cnt].nxt = head[from];
	head[from] = cnt;
}

void dijkstra() { //求起点s到每个点的最短路
	dis[s] = 0;
	for (int i = 1; i <= n; i++) { //选取一个最短路长度最小的结点
		int u, dmin = INF;
		for (int j = 1; j <= n; j++) {
			if (vis[j] == 0 && dis[j] < dmin) {
				u = j;
				dmin = dis[j];
			}
		}
		vis[u] = 1; //这个点移到 S 集合中
		for (int i = head[u]; i; i = edge[i].nxt) { //执行松弛操作
			v = edge[i].to, w = edge[i].dis;
			if (dis[u] + w < dis[v])
				dis[v] = dis[u] + w;
		}
	}
}

int main() {
	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		add_edge(u, v, w);
	}
	for (int i = 1; i <= n; i++)
		dis[i] = INF;
	dijkstra();
	for (int i = 1; i <= n; i++)
		cout << dis[i] << " ";
	return 0;
}

/*
dijkstra过程：
	将结点分成两个集合：已确定最短路长度的点集（记为 S 集合）的和未确定最短路长度的点集（记为 T 集合）。
	一开始所有的点都属于 T 集合。
	初始化 dis[s] = 0，其他点的 dis 均为 +INF。
	然后重复这些操作：
	从 T 集合中，选取一个最短路长度最小的结点，移到 S 集合中。
	对那些刚刚被加入 S 集合的结点的所有出边执行松弛操作。
	直到 T 集合为空，算法结束。
*/