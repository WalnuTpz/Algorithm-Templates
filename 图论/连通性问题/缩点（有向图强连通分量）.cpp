#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 10010, maxm = 100010;

int n, m, u[maxn], v[maxn], a[maxn], idx, ans;
int dfn[maxn], low[maxn], instk[maxn], scc[maxn];
int in[maxn], dp[maxn];

vector<int> g[maxn], g2[maxn];
stack<int> st;

void tarjan(int u) {
	dfn[u] = low[u] = ++idx;
	st.push(u);
	instk[u] = 1;
	for (auto v : g[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (instk[v]) //只有在栈中的点对应的边才可以作为返祖边来更新
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) { //找到了一个SCC
		while (st.top() != u) {
			instk[st.top()] = 0;
			scc[st.top()] = u;
			a[u] += a[st.top()];
			st.pop(); //将u自己也出栈
		}
		st.pop();
		instk[u] = 0;
		scc[u] = u;
	}
}

void topo() {
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (scc[i] == i && !in[i]) {
			q.push(i);
			dp[i] = a[i];
		}
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : g2[u]) { //dp[i]代表以i为终点的路径的最大权值和
			dp[v] = max(dp[v], dp[u] + a[v]);
			in[v]--;
			if (!in[v])
				q.push(v);
		}
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i];
		g[u[i]].push_back(v[i]);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i);
	for (int i = 1; i <= m; i++) {
		int x = scc[u[i]], y = scc[v[i]];
		if (x != y) {
			g2[x].push_back(y);
			in[y]++;
		}
	}
	topo();
	for (int i = 1; i <= n; i++) //答案就是每条路径的最大权值和的max
		ans = max(ans, dp[i]);
	cout << ans << endl;
	return 0;
}

/*
缩点就是将一个有向图中的强连通分量（SCC)各自压缩为一个点，从而变为有向无环图的过程。变成有向无环图以后，就可以通过(拓扑排序 + dp)
来求出权值和最大的路径的权值和

总体上来说，缩点要用到tarjan算法，与点双连通分量/边双连通分量中的算法基本一致，但有一些细微的区别。
(1) 此时是有向图，所以只添加单向边，tarjan中也不需要参数fa来判断走到了上一条走过的边(fa, u)
(2) 栈中此时用来储存未加入SCC的所有点
然后再来看这个算法本身，在遍历完u的所有子节点后，某些子树会通过非dfs树中的边返回u（它们会和u形成一个SCC），而某些不会返回。
假如low[u] == dfn[u]，说明找到了可以返回u的子树。此时将u作为这个SCC的根节点，进行缩点操作：将子树中的所有节点出栈，并将它们的根标记为u，
并将它们的权值累加到u的权值上。注意到对于那些不会返回的子树，它们在各自的dfs结束以后每个节点会提前出栈（作为一个单点SCC），
所以它们不会影响u对应的SCC。

在缩点进行完成后，再重新建一次图：对于图中的每条边，如果它们属于同一个SCC，则忽略；反之加入新的图g2。此时得到的新图是一个有向无环图，
再使用(拓扑排序 + dp)求出最大路径权值和即可
*/