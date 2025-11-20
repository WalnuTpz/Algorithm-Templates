#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll, ll>;
const int maxn = 100010, inf = 2147483647;

int n, m, s, u, v, w,  vis[maxn];
ll dis[maxn];

vector<pii> g[maxn];
priority_queue<pii, vector<pii>, greater<pii>> pq;

void dijkstra(int s) { //求起点s到每个点的最短路
	dis[s] = 0;
	pq.push({0, s}); //这里采用C++自带二元组编写
	while (!pq.empty()) { //当堆中还有元素
		auto [d, u] = pq.top(); //取出堆顶，也就是当前距离起点最近的点
		pq.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (auto [v, w] : g[u]) {
			if (vis[v])
				continue;
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				pq.push({dis[v], v}); //每次松弛成功，把关于当前点的信息压入堆
			}
		}
	}
}

int main() {
	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		g[u].push_back({v, w});
	}
	for (int i = 1; i <= n; i++)
		dis[i] = inf;
	dijkstra(s);
	for (int i = 1; i <= n; i++)
		cout << dis[i] << " ";
	return 0;
}

/*
注1：priority_queue<(数据类型)>的定义方法默认是大根堆。只有priority_queue<(数据类型),vector<(数据类型)>,greater<(数据类型)> >的方法才能定义小根堆。另外，应该用空格分开两个连在一起的尖括号(<<或>>)，否则编译器会把它识别成流读取运算符。
 	当然，你也可以选择重载运算符，不过我觉得这样更好些。毕竟不少人不会重载。
 	另外，优先队列虽然等价于堆，但是内部原理是通过给予变量一个优先值来实现的，与堆不同。
注2：C++自带的二元组pair,定义方法是pair<(数据类型1),(数据类型2)>(名称)。相当于一个包含两个变量的结构体。pair中的两个成员使用.first和.second进行访问。在优先队列里，pair是以first为第一关键字、以second为第二关键字排序的。向pair中插入元素可以直接像结构体一样赋值，也可以使用make_pair()插入。

还有一种写法：
直接用大根堆    priority_queue<pr> q;
并且后面用    q.push(make_pair(-dis[v], v));
把dis换成它的负数，和小根堆/重载运算符的效果就一样了
*/