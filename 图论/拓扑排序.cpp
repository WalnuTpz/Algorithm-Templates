#include <bits/stdc++.h>
using namespace std;

const int N = 1010, M = 10010;
int n, m, cnt, u, v, w, head[N], in[N];
queue<int> q;

struct Edge {
	int to;
	int nxt;
} edge[M];

void add_edge(int from, int to) {
	cnt++;
	edge[cnt].to = to;
	edge[cnt].nxt = head[from];
	head[from] = cnt;
}

void topo() { //拓扑排序
	for (int i = 1; i <= n; i++)
		if (in[i] == 0)
			q.push(i);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		cout << u << " "; //输出当前节点
		for (int i = head[u]; i != 0; i = edge[i].nxt) {
			int v = edge[i].to; //这条边指向的节点
			in[v]--; //节点的入度减一
			if (in[v] == 0) //当前的入度为零时，可以入队参与下一轮拓扑排序
				q.push(v); //因为此时它前面的点已经排完了
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		in[v]++;
	}
	topo();
	return 0;
}
