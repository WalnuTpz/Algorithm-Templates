#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 200010;

int n, u, v, w, dp[maxn], st;

vector<pair<int, int>> g[maxn];

void dfs(int u, int fa) {
	for (auto &[v, w] : g[u]) {
		if (v == fa)
			continue;
		dp[v] = dp[u] + w;
		if (dp[v] > dp[st]) //dp[st]对应的就是dp数组的最大值
			st = v;
		dfs(v, u);
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	dfs(1, 0);
	dp[st] = 0;
	dfs(st, 0);
	cout << dp[st] << endl;
	return 0;
}

/*
树上任意两节点之间最长的简单路径即为树的直径，并且一棵树可以有多条直径

可以用两次dfs或树形dp的方法求出树的直径长度，并也可以通过记录前一个节点的方法求出具体直径。这里讲两次dfs的方法：首先任选一个点
（这里选择点1）作为起点，然后进行一次dfs，求出它到所有点的距离dp[i]，然后我们可以知道直径的一端对应的dp[i]一定是最大的。
因为假设直径端点为s, t，且dp[z] > dp[t]，那么经过简单画图和推理可得d(s, z) > d(s, t)，这与直径的定义矛盾，所以dp[t]是最大的一定成立。
然后找到最大的点对应的下标，作为新的起点再进行一次dfs，此时求出的最大的dp[i]就是直径的长度了（它对应的点也就是直径的另一个端点）

有一点需要注意的是，这个方法没法处理边长为负数时的情况
*/
