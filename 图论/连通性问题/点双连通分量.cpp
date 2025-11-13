#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 500010;

int n, m, u, v, idx, ans;
int dfn[maxn], low[maxn];

vector<int> g[maxn], bcc[maxn];
stack<int> st;

void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++idx;
	int son = 0;
	st.push(u);
	for (auto v : g[u]) {
		if (!dfn[v]) {
			son++;
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				ans++;
				while (st.top() != v) { //将子树v全部出栈并加入当前bcc
					bcc[ans].push_back(st.top());
					st.pop();
				}
				bcc[ans].push_back(st.top()); //节点v出栈并加入当前bcc
				st.pop();
				bcc[ans].push_back(u); //节点u加入当前bcc
			}
		} else if (v != fa)
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		ans++;
		while (st.top() != v) { //将子树v全部出栈并加入当前bcc
			bcc[ans].push_back(st.top());
			st.pop();
		}
		bcc[ans].push_back(st.top()); //节点v出栈并加入当前bcc
		st.pop();
		bcc[ans].push_back(u); //节点u加入当前bcc
	}
	if (fa == 0 && son == 0) //孤立点，也是一个单独的点双
		bcc[++ans].push_back(u);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			while (!st.empty())
				st.pop();
			tarjan(i, 0);
		}
	}
	cout << ans << endl;
	for (int i = 1; i <= ans; i++) {
		cout << bcc[i].size() << " ";
		for (auto u : bcc[i])
			cout << u << " ";
		cout << endl;
	}
	return 0;
}

/*
点双连通子图是指其中的每个点都不是割点（去掉它以后这个图依然是连通的）。也就是图中任意两个点之间至少有两条经过的点不同的路径可以相互到达，
这样让去掉的那个点对应的路径断掉以后依然可以走另一条路径到达。
点双连通分量是指无向图中的一个极大的点双联通子图（也就是在点双连通的前提下每个子图要越大越好）

然后来看如何求一个图中的所有点双连通分量。首先用tarjan算法求出割点，然后对于割点和它的每一个没有返祖边（即满足low[v] >= dfn[u]）的子树v，
都是一个单独的点双连通分量。因为如果子树有返祖边，那么返祖边就能作为定义中的第二条路径，此时去掉u以后依然可以走那条路到达。
重要的是，这些没有返祖边的子树之间属于不同的点双。我们假设子树的根为v1, v2...因为它们属于不同的子树，所以在dfs完子树v1以后要返回根节点u，
再进行子树v2的dfs，所以这些子树之间只通过u对应的路径连接在一起，没有第二条路径连接在一起，所以它们不属于一个点双而是各自独立的）

为了记录子树的所有节点，我们在tarjan时使用一个栈记录遇到的节点，然后如果遇到没有返祖边的节点v，就说明遇到了一个新的点双，此时需要不断出栈
直到将v也出栈（此时就是出栈了整个子树v），然后把这些点还有节点u全部加入一个新的点双。还需要注意的是孤立点也是一个单独的点双，由于题目中
可能出现自环，所以我们需要统计u的真儿子（dfn[v] == 0的点。因为对于自环v == u，此时dfn[v] = dfn[u] > 0，所以不满足）的数量而不是直接统计
g[u].size()。最后一点是，如果图中的某个极大连通子图自己就是一个点双，那么在dfs到子图中的最后一个节点v时，它的下一条边一定能通过与现在的
dfs路径不同的另一条路径返回根节点，那么此时low[v] = dfn[root] = 1，此时进行dfs的回溯，并在回溯中将所有节点的low都被更新为了1，
当回溯到根节点时，此时有low[v] = 1 >= dfn[u] = 1，所以整个子图就变成了一个点双。
*/

