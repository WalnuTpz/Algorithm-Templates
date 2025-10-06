#include <bits/stdc++.h>
using namespace std;
const int N = 10010, M = 100010;
int n, m, cnt, u, v, w, head[N];

struct Edge {
	int to;
	int dis;
	int nxt;
} edge[M * 2];

void add(int from, int to, int dis) {
	cnt++; //边的数量
	edge[cnt].to = to; //目标点初始化
	edge[cnt].dis = dis; //权值
	edge[cnt].nxt = head[from]; //下一条边的编号
	head[from] = cnt; //以from为起点的边的编号更新
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		add_edge(u, v, w);
	}

	for (int i = head[x]; i; i = edge[i].nxt) {
		//遍历
	}
	return 0;
}
