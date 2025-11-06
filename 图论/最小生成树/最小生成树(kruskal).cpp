#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10, M = 2e5 + 10;
int n, m, ans, cnt, fa[N];

struct Edge {
	int u, v, w;
} edge[M];

bool cmp(Edge x, Edge y) {
	return x.w < y.w;
}

int find(int x) {
	if (fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}

void uni(int x, int y) {
	int r1 = find(x), r2 = find(y);
	fa[r2] = r1;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1; i <= m; i++)
		cin >> edge[i].u >> edge[i].v >> edge[i].w;
	sort(edge + 1, edge + m + 1, cmp); //把边的权值从小到大排序
	for (int i = 1; i <= m; i++) {
		int u = edge[i].u, v = edge[i].v, w = edge[i].w;
		if (find(u) == find(v)) //和之前选取的边成环（即在并查集中祖先相同），跳过
			continue;
		uni(u, v); //否则选取这条边，并累加边的权值
		ans += w;
		cnt++;
	}
	if (cnt == n - 1) //选取的边数少于(n - 1)，说明不存在生成树
		cout << ans << endl;
	else
		cout << "orz" << endl;
	return 0;
}
