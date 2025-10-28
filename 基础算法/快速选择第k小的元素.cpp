#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;

int n, k, a[maxn];

int qselect(int l, int r) { //快速选择函数
	if (l >= r)
		return a[l];
	int l1 = l, r1 = r, key = l + rand() % (r - l + 1);
	swap(a[key], a[i]);
	while (l1 < r1) {
		while (l1 < r1 && a[r1] >= a[key])
			r1--;
		while (l1 < r1 && a [l1] <= a[key])
			l1++;
		if (l1 < r1)
			swap(a[l1], a[r1]);
	}
	//出循环后 i == j,且为key实际所在的下标
	if (k == i) //根据l1与k的大小关系选择新的递归区间
		return a[i];
	if (k <= i - 1)
		return qselect(l, i - 1);
	if (i + 1 <= k)
		return qselect(i + 1, r);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	srand(time(0));
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	cout << qselect(1, n) << endl;;
	return 0;
}

/*
等价于nth_element(a + 1, a + k, a + n + 1)
*/
