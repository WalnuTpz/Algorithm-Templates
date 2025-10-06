#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
int n, m, p, x, y, fa[N];

int find(int x) { //找到对应集合树的根节点（祖先节点）
	if (fa[x] != x) //fa[x] == x 时说明是根
		fa[x] = find(fa[x]); //路径压缩，把x上面所有的节点的父亲全部修改为根节点，减少后续查找时间
	return fa[x];
}

void uni(int x, int y) { //合并
	int r1 = find(x), r2 = find(y);
	fa[r2] = r1;
}

int main() {
	cin >> n >> m >> p;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i =  1; i <= m; i++) {
		cin >> x >> y;
		uni(x, y);
	}
	for (int i = 1; i <= p; i++) {
		cin >> x >> y;
		int r1 = find(x), r2 = find(y);
		if (r1 != r2)
			cout << "No" << endl;
		else
			cout << "Yes" << endl;
	}
	return 0;
}
