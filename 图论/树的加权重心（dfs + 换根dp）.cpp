#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, head[N], cnt, w[N], siz[N], u, v;
long long f[N], ans = 2147483647 * 65535;

//本题代码有误，请慎重采用
struct Edge {
	int to, nxt;
} edge[N * 2];

void add_edge(int from, int to) {
	cnt++;
	edge[cnt].to = to;
	edge[cnt].nxt = head[from];
	head[from] = cnt;
}

void dfs(int u, int fa, int dep) { //预处理f[1]和size[]
	siz[u] = w[u]; //注意本题是带权重心
	for (int i = head[u]; i != 0; i = edge[i].nxt) {
		int to = edge[i].to;
		if (to != fa) {
			dfs(to, u, dep + 1);
			siz[u] += siz[to];
		}
	}
	f[1] += w[u] * dep;
}

void dp(int u, int fa) {
	for (int i = head[u]; i != 0; i = edge[i].nxt) {
		int to = edge[i].to;
		if (to != fa) {
			f[to] = f[u] + (siz[1] - siz[to]) - siz[to];
			dp(to, u);
		}
	}
	ans = min(ans, f[u]);
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> u >> v;
		if (u) {
			add_edge(i, u);
			add_edge(u, i);
		}
		if (v) {
			add_edge(i, v);
			add_edge(v, i);
		}
	}
	dfs(1, 0, 0);
	dp(1, 0);
	cout << ans << endl;
	return 0;
}

/*
树的重心的定义：
	树若以某点为根，使得该树最大子树的结点数最小，那么这个点则为该树的重心，一棵树可能有多个重心。

树的重心的性质：
	1、树上所有的点到树的重心的距离之和是最短的，如果有多个重心，那么总距离相等。
	2、插入或删除一个点，树的重心的位置最多移动一个单位。
	3、若添加一条边连接2棵树，那么新树的重心一定在原来两棵树的重心的路径上。

怎么求树的重心：
    定义几个数组：f[u]表示以u为根的总距离，siz[u]表示以u为根的子树的大小（结点数）。
    显然，ans = min(f[i],1 <= i <= n)
    首先我们任意以一个点为根dfs一遍，求出以该点为根的总距离。方便起见，我们就以1为根。
    接下来就是转移，对于每个u能达到的点v，有：f[v] = f[u] + (siz[1] - siz[v]) - siz[v]
    怎么来的呢？试想，当根从u变为v的时候，v的子树的所有节点原本的距离要到u，现在只要到v了，
每个结点的距离都减少1，那么总距离就减少siz[v]，同时，以v为根的子树以外的所有节点，原本只要到
u就行了，现在要到v，每个节点的路程都增加了1，总路程就增加了siz[1] - siz[v]，其中siz[1]就是我们
预处理出来的整棵树的大小，减去siz[v]就是除以v为根的子树以外的结点数。
    最后取最小值，得解。时间复杂度O(n)
*/