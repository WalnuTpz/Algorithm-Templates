#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 500010, maxm = 2000010;

int n, m, u, v, idx, ans;
int dfn[maxn], low[maxn];

vector<pair<int, int>> g[maxn];
vector<int> bcc[maxn];
stack<int> st;

void tarjan(int u, int fid) {
	dfn[u] = low[u] = ++idx;
	st.push(u);
	for (auto &[v, id] : g[u]) {
		if (!dfn[v]) {
			tarjan(v, id);
			low[u] = min(low[u], low[v]);
		} else if (id != fid)
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		ans++;
		while (st.top() != u) {
			bcc[ans].push_back(st.top());
			st.pop();
		}
		bcc[ans].push_back(st.top());
		st.pop();
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) { //dfn[i] == 0，说明是一个单独的连通快，进行dfs
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
边双连通子图是指其中的每条边都不是割边（去掉它以后这个图依然是连通的）。也就是图中任意两个点之间至少有两条经过的边不同的路径可以相互到达，
这样让去掉的那条边对应的路径断掉以后依然可以走另一条路径到达。

实际上对于连通性的要求：点双 > 边双 > 普通连通分量。首先因为前两个必须是双连通，第三个只需要是单连通；然后有一种情况是连接两个边双的
两条边不同的路径都经过同一个点，此时整个图满足边双的条件，但易知这个点是割点，所以不满足点双的条件，所以点双要求更高。

为了求边双，依旧要使用tarjan算法。
(1)第一种算法是求出图中所有的割边，并把它们去掉（进行标记isbridged）。此时得到的新图中的每一个连通分量都是原图中的一个边双，
可以用dfs求得。（这里没有采用这种做法）
(2)第二种算法需要和点双一样维护一个节点栈。但注意点双是在发现割点时记录新的点双并进行出栈；但边双是在遍历完当前节点的所有子节点以后，
假如low[u] == dfn[u]，说明没有返祖边，此时(u, fa)形成了一个边双，那么此时记录新的边双并出栈。为什么不能在找到割边low[v] > dfn[u]时就
出栈呢？有一个可能的原因是假如整颗树都是一个边双的时候那个判断条件会把这个漏掉，但原判断条件依然可以处理这一点。
实际上，此时就是通过dfs把原先的无向图转化为有向图，此时边双就被转化为了一个有向图中的强连通分量，所以第二种算法实际上也是
求有向图中的强连通分量的算法。

更详细的解析：
我们在求点双时，暴力地将割点的条件直接修改为 low[v]>=dfn[u] 而省略根节点的判断。这样我们可以将剩余的节点与根节点一起放入一个点双。
但很显然，如果图中不存在桥，就不可能使条件 low[v]>dfn[u] 成立。我们考虑在每一次搜索前，建立一个虚拟源点0指向原来的根，
这样，原先我们新加的虚拟边(0, root)就成为了虚拟桥。这样就使图中至少存在一个桥。这种方法也可以解决独立节点的问题。
*/

