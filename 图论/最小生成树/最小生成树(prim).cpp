#include <bits/stdc++.h>
using namespace std;
const int N = 5010, M = 200010, INF = 0x7ffffff;
int n, m, cnt, u, v, w, head[N];
int tot, now, dis[N], vis[N], ans, flag = 1;

struct Edge {
	int to;
	int dis;
	int nxt;
} edge[M * 2];

void add(int from, int to, int dis) {
	cnt++;
	edge[cnt].to = to;
	edge[cnt].dis = dis;
	edge[cnt].nxt = head[from];
	head[from] = cnt;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
	}

	for (int i = 1; i <= n; i++) //dis[i]表示当前选取的点集中的点到i的最短距离
		dis[i] = INF;
	now = 1;
	vis[now] = 1; //vis[i] == 1表示已经选取该点
	for (int i = head[now]; i; i = edge[i].nxt) {
		int v = edge[i].to, w = edge[i].dis;
		dis[v] = min(dis[v], w);
	}

	while (tot < n - 1) { //tot == (n - 1)时结束
		int minn = INF;
		for (int i = 1; i <= n; i++) {
			if (!vis[i] && dis[i] != INF) { //枚举没经过（就不会成环）并且可以到达的点
				if (dis[i] < minn) {
					minn = dis[i];
					now = i;
				}
			}
		}
		if (minn == INF) { //没找到，说明没有生成树
			flag = 0;
			break;
		}
		vis[now] = 1; //选取dis最小的点
		tot++;
		ans += dis[now];
		for (int i = head[now]; i; i = edge[i].nxt) { //根据这个点进一步更新其他点的dis（从这个点出发可以到达更多的点）
			int v = edge[i].to, w = edge[i].dis;
			dis[v] = min(dis[v], w);
		}
	}
	if (flag)
		cout << ans << endl;
	else
		cout << "orz" << endl;
	return 0;
}
