#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define ll long long
int n, q, u, v, c, x, B;

void solve() {
	cin >> n >> q;
	ll sumc = 0, samec = 0;
	B = sqrt(n); //分块的大小
	vector<int> a(n + 10, 0), flag(n + 10, 0);
	vector<unordered_map<int, ll>> colorsum(n + 10);
	vector<vector<pii>> g(n + 10), g2(n + 10);
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i < n; i++) {
		cin >> u >> v >> c;
		g[u].push_back({v, c});
		g[v].push_back({u, c});
		sumc += c; //所有边的总权值
	}
	for (int u = 1; u <= n; u++) //度数大于B的点是“重顶点”，进行标记
		if (g[u].size() > B)
			flag[u] = 1;
	for (int u = 1; u <= n; u++) { //g2用于储存重顶点的所有重顶点邻居，用于优化更新时颜色的时间复杂度
		if (flag[u]) {
			for (pii i : g[u]) {
				int v = i.first, c = i.second;
				if (flag[v])
					g2[u].push_back({v, c});
			}
		}
	}
	for (int u = 1; u <= n; u++) {
		for (pii i : g[u]) {
			int v = i.first, c = i.second;
			if (flag[u]) //colorsum用于储存与重顶点相连的每种颜色的边的权值之和
				colorsum[u][a[v]] += c; //如colorsum[u][x]表示与重顶点u相连的颜色为x的边的权值之和
			if (u < v && a[u] == a[v]) //计算相同颜色的边的权值之和
				samec += c;
		}
	}
	for (int k = 1; k <= q; k++) {
		cin >> v >> x;
		if (a[v] == x) { //颜色不变，直接输出答案
			cout << sumc - samec << '\n';
			continue;
		}
		int a0 = a[v];
		ll changec = 0;
		if (flag[v]) { //对于重顶点，直接查询两种颜色的权值之和更新同色权值和的改变量
			ll c1 = 0, c2 = 0;
			if (colorsum[v].count(a0)) //旧的颜色
				c1 = colorsum[v][a0];
			if (colorsum[v].count(x)) //新的颜色
				c2 = colorsum[v][x];
			changec = c2 - c1;
		} else { //对于轻顶点，遍历查询两种颜色的权值之和并更新同色权值和的改变量
			for (pii i : g[v]) {
				int u = i.first, c = i.second;
				if (a[u] == a0)
					changec -= c;
				if (a[u] == x)
					changec += c;
			}
		}
		samec += changec; //更新同色权值和
		a[v] = x;
		if (flag[v]) { //对于重顶点，只遍历并更新它的重顶点邻居(g2)，因为遍历它的所有邻居会超时
			for (pii i : g2[v]) {
				int u = i.first, c = i.second;
				colorsum[u][a0] -= c;
				colorsum[u][x] += c;
			}
		} else { //对于轻顶点，直接遍历更新它的重顶点邻居的颜色权值和
			for (pii i : g[v]) {
				int u = i.first, c = i.second;
				if (flag[u]) {
					colorsum[u][a0] -= c;
					colorsum[u][x] += c;
				}
			}
		}
		cout << sumc - samec << '\n'; //不同色权值和就是总权值和减去同色权值和
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
		solve();
	return 0;
}

/*
总代价是所有 颜色不同 的边权之和。
一个等价的计算方式是：
总代价 = (所有边的权值总和) - (所有颜色相同的边的权值总和)

所有边的权值总和是一个固定值。因此，我们只需要高效地维护和查询 颜色相同的边（单色边） 的权值总和即可。
当一个顶点 v 的颜色从 c_old 变为 c_new 时，哪些单色边的状态会改变？
只有与顶点 v 相连的边才可能受影响。

对于 v 的一个邻居 u（边 (v, u) 的权值为 w）：
如果 u 的颜色是 c_old：这条边之前是单色边（c_old -- c_old），现在变成了异色边（c_new -- c_old）。单色边权值总和减少 w。
如果 u 的颜色是 c_new：这条边之前是异色边（c_old -- c_new），现在变成了单色边（c_new -- c_new）。单色边权值总和增加 w。
如果 u 的颜色既不是 c_old 也不是 c_new：这条边之前是异色边，现在还是异色边。对单色边权值总和没有影响。
因此，总代价的变化量 Δ 为：
Δ = (v 的颜色为 c_old 的邻居的边权之和) - (v 的颜色为 c_new 的邻居的边权之和)
新的总代价 = 旧的总代价 + Δ。

瓶颈与解决方案
现在的问题转化为：对于任意顶点 v 和颜色 k，如何快速计算出 v 的颜色为 k 的所有邻居的边权之和？
朴素做法：每次查询时，遍历 v 的所有邻居。如果邻居数量（即 v 的度）很大，这个操作会很慢。
		  最坏情况下，查询一次的时间复杂度是 O(N)，总时间复杂度是 O(N*Q)，无法通过。
高效算法：平方根分解 (Square Root Decomposition)
我们可以根据顶点的度（degree）将其分为“轻顶点”和“重顶点”。

选择一个阈值 B (通常取 sqrt(N) )。
重顶点 (Heavy)：度 > B 的顶点。
轻顶点 (Light)：度 <= B 的顶点。
关键性质：
一个轻顶点的邻居数量不超过 B。
重顶点的数量不超过 2*(N-1) / B。如果 B = sqrt(N)，则重顶点的数量为 O(sqrt(N))。
*/
