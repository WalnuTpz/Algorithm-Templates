#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;

int n, a[maxn];

void qsort(int l, int r) { //快速排序，从小到大
	if (l >= r)
		return;
	int i = l, j = r, key = l + rand() % (r - l + 1); //随机化pivot的位置
	swap(a[key], a[i]);
	while (i < j) {
		while (i < j && a[j] >= a[key])
			j--;
		while (i < j && a[i] <= a[key])
			i++;
		swap(a[i], a[j]);
	}
	//出循环后 i == j,且为key实际所在的下标
	//排一次，分为三个区间  [l,i - 1] i [i + 1,r]
	qsort(l, i - 1);
	qsort(i + 1, r);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	srand(time(0));
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	qsort(1, n);
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	return 0;
}
