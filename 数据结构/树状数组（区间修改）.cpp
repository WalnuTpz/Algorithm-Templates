#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
int n, m, a[N], b[N], t[N], op, x, y, k; //区间修改，单点查询

int lowbit(int x) {
	return x & (-x);
}

void add(int x, int k) { //b[x] += k，并更新t数组
	for (int i = x; i <= n; i += lowbit(i)) {
		t[i] += k;
	}
}

int sum(int x) { //求b[1]~b[x]的区间和，即a[x]
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		sum += t[i];
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = a[i] - a[i - 1]; //差分数组
		add(i, b[i]);
	}

	for (int i = 1; i <= m; i++) {
		cin >> op;
		if (op == 1) {
			cin >> x >> y >> k; //a[x]~a[y] += k
			add(x, k);
			add(y + 1, -k);
		} else if (op == 2) {
			cin >> x;
			cout << sum(x) << endl;
		}
	}
	return 0;
}


