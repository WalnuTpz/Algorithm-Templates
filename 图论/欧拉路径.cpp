#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 200010;

int n, m, u, v, cnt1, cnt2;
int in[maxn], out[maxn], cur[maxn];

vector<int> g[maxn];
stack<int> st;

void dfs(int u) {
	for (int i = cur[u]; i < g[u].size(); i = cur[u]) {
		int v = g[u][i];
		cur[u]++;
		dfs(v);
	}
	st.push(u);
}

int main() {
	int flag = 1, s = 1;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		in[v]++;
		out[u]++;
	}
	for (int i = 1; i <= n; i++) {
		sort(g[i].begin(), g[i].end());
		if (in[i] != out[i]) {
			flag = 0;
			if (in[i] - out[i] == -1) { //出度 = 入度 + 1，是起点
				s = i;
				cnt1++;
			} else if (in[i] - out[i] == 1) { //入度 = 出度 + 1，是终点
				cnt2++;
			} else { //其余情况下一定没有欧拉路径
				cout << "No" << endl;
				return 0;
			}
		}
	}
	if (!flag && !(cnt1 == 1 && cnt2 == 1)) { //有多个起点或终点，也没有欧拉路径
		cout << "No" << endl;
		return 0;
	}
	dfs(s);
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	return 0;
}

/*
欧拉路径是指恰好遍历图中所有边的一条路径，如果它是回路那么这个路径也被叫做欧拉回路。本题要求输出字典序最小的欧拉路径。

对于普通欧拉路径，它的起点一定满足出度 = 入度 + 1，并且它的终点一定满足入度 = 出度 + 1，但注意这样的点各自只能存在一个。
如果所有点的入度都等于出度，为了让路径字典序最小，就把1作为起点。然后在遍历时，为了让字典序最小，需要将每个点邻接表中的所有点
升序排序。

然后考虑如何遍历。首先从小到大遍历点u的所有邻居v，我们用cur[u]表示当前应该从什么位置开始，然后注意循环语句
for (int i = cur[u]; i < g[u].size(); i = cur[u])，因为在更深层次的递归中可能会再次遇到u，就会把g[u][i + 1]或这更后面的点也访问了，
所以当前循环中的下一个点不应该是g[u][i + 1]而应该是g[u][cur[u]]。最后考虑dfs怎么得到路径，它应该是在回溯中得到而不是在遍历开始时
得到。因为dfs遍历完一个子树后会回溯并开始遍历下一个子树，也就是遍历的结点时上一个子树的最后一个节点到新子树的第一个节点，但这里
显然是不存在一条路径的（否则这两个点应该属于同一个子树），也就是会出现跳跃。但在回溯时是从路径的尾结点回溯到开头节点，所以这样在
遍历每棵子树时就会得到连续路径。但注意此时得到的路径是反过来的，所以要使用栈，就可以在最后倒序输出得到真实路径。
*/
