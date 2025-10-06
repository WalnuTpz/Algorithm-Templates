#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
int n, m, a[N], t[N], op, x, y; //单点修改，区间查询
//t[x]保存以x为根的子数中叶子节点值的和

int lowbit(int x) {
	return x & (-x);
}

void add(int x, int k) { //a[x] += k，并更新t数组
	for (int i = x; i <= n; i += lowbit(i)) { //i的父亲节点是i + lowbit(i)
		t[i] += k;
	}
}

int sum(int x) { //求a[1]~a[x]的前缀和
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i)) { //一直进行i - lowbit(i)就可以得到原数组的前缀和
		sum += t[i];
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		add(i, a[i]);
	}

	for (int i = 1; i <= m; i++) {
		cin >> op >> x >> y;
		if (op == 1) {
			add(x, y);
		} else if (op == 2) { //实际上单点查询的话就让x = y就好了
			int sum1 = sum(x - 1), sum2 = sum(y);
			cout << sum2 - sum1 << endl;
		}
	}
	return 0;
}

/*
lowbit(x)是非负整数x在二进制下的最低位1及其后面的0构成的数
为什么可以用 x & (-x) 计算？
因为x的最低位1和后面的0是10000这样的形式
而-x是x取反加1，取反后变01111，再加1就是10000
所以x & (-x)就是lowbit(x)
*/
