#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 1010;

int n, m, e, u, v, chose[maxn], vis[maxn], ans;

vector<int> g[maxn];

int dfs(int u) {
	for (auto v : g[u]) {
		if (vis[v])
			continue;
		vis[v] = 1;
		if (!chose[v] || dfs(chose[v])) { //v目前没人占或者v的原主人可以找到新的物品来配对
			chose[v] = u; //u变成v的新主人，并且说明已找到增广路
			return 1;
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> e;
	for (int i = 1; i <= e; i++) {
		cin >> u >> v;
		g[u].push_back(v);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			vis[j] = 0;
		if (dfs(i)) //找到增广路，匹配数量加一
			ans++;
	}
	cout << ans << endl;
	return 0;
}

/*
n个人，m件物品，e条边，求最多可以形成多少组（人->物品并且不重复的）匹配

为了寻找最大匹配，我们需要使用匈牙利算法寻找增广路。增广路是未匹配边和已匹配边交替出现并且首尾都是未匹配边的路径，
所以易知增广路中未匹配边的数量比已匹配边的数量恰好多1。找到增广路以后，将其中所有边的匹配状态反转（已匹配和未匹配互换），
那么此时已匹配边的数量就多了一个，依次对所有左侧的点寻找增广路，那么已匹配边的数量就会不断增加，直到最后不再增加了就说明
已经找到了最大匹配（但这个不用在程序中显式地判断）

一个有趣的点是，假如dfs(chose[v])，也就是v的原主人u'可以找到新的物品v'来配对，此时会执行chose[v] = u，那么原来的匹配
u - v -- u' - v变为了u -- v - u' -- v'（已匹配：--，未匹配：-），此时自动实现了匹配状态的翻转，所以翻转是不用手动实现的
*/
