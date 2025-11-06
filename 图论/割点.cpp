#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 20010;

int n, m, u, v, root, rootson, idx, ans;
int dfn[maxn], low[maxn], iscut[maxn];

vector<int> g[maxn], cut;

void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++idx;
	for (auto v : g[u]) {
		if (!dfn[v]) {
			if (u == root)
				rootson++;
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (u != root && low[v] >= dfn[u]) //不是根节点并且low[v] >= dfn[u]，说明是割点
				iscut[u] = 1;
		} else if (v != fa) //此时v是祖先（相当于题解中的w）
			low[u] = min(low[u], dfn[v]);
	}
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
		if (!dfn[i]) { //dfn[i] == 0，说明是一个单独的连通快，进行dfs
			root = i;
			rootson = 0;
			tarjan(i, 0);
			if (rootson >= 2) //根节点的孩子数量 >= 2，说明是割点
				iscut[i] = 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (iscut[i]) {
			ans++;
			cut.push_back(i);
		}
	}
	cout << ans << endl;
	for (auto u : cut)
		cout << u << " ";
	return 0;
}

/*
如果一个图中去掉某个点和与它相连的所有边，那么称这个点为割点

为了求出图中的割点，首先对图进行dfs（为什么要dfs后面会解释），求出每个点u在dfs中第一次被访问的序号dfn[u]。由于图不一定是连通的，
所以可能要对每个连通块各自进行一次dfs。然后考虑什么情况下会出现割点：
(1)u是本次dfs的根节点，如果它的儿子个数 >= 2，那么删去它以后它的儿子之间会断开，所以此时它是割点
(2)u不是根节点，然后在dfs树中它下面的点v如果要前往它上面的点w必须经过它（而不是可以经过别的点绕过去），此时它也是割点

第一个性质容易判断。下面考虑如何判断第二个性质，我们考虑找出下面的点v是否可以绕过u到达上面的点w。所以令low[u]为从 u 出发，
沿着“先往子树里走若干步（零步也行），再用至多一条返祖边往上跳”，能到达的最早出现的结点（即最小的 dfn）的编号。假如low[v] < dfn[u]，
就说明可以绕过v到达更上面的点w。此时u不是割点，反之是割点。

然后考虑如何求出low[u]，首先它至少是dfn[u]；然后在子树走零步直接往上跳，也就是如果有返祖边(u, w)，则是dfn[w]；
最后是先往子树走，然后再往上跳，也就是low[v]。三部分取min就是low[u]的最终值
*/
