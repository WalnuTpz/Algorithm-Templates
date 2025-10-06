#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;

int n, a[maxn];

void qsort(int l, int r) { //快速排序，从小到大
	if (l >= r)
		return;
	int l1 = l, r1 = r, key = l;
	while (l1 < r1) {
		while (l1 < r1 && a[r1] >= a[key])
			r1--;
		while (l1 < r1 && a [l1] <= a[key])
			l1++;
		swap(a[l1], a[r1]);
	}
	swap(a[key], a[l1]);  //出循环后 l1 == r1,且为key实际所在的下标
	//排一次，分为三个区间  [l,l1 - 1] l1 [l1 + 1,r]
	qsort(l, l1 - 1);
	qsort(l1 + 1, r);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	qsort(1, n);
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	return 0;
}
