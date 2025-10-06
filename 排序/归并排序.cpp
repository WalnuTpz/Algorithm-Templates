#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;

int n, a[maxn], b[maxn];

void mergesort(int l, int r) {
	if (l >= r)
		return;
	int mid = (l + r) / 2;
	mergesort(l, mid); //先对前半部分排序
	mergesort(mid + 1, r); //再对后半部分排序
	int i = l, j = mid + 1, tot = l; //最后合并前后两个单调序列
	while (i <= mid && j <= r) {
		if (a[i] <= a[j]) {
			b[tot] = a[i];
			tot++;
			i++;
		} else {
			b[tot] = a[j];
			tot++;
			j++;
		}
	}
	while (i <= mid) {
		b[tot] = a[i];
		tot++;
		i++;
	}
	while (j <= r) {
		b[tot] = a[j];
		tot++;
		j++;
	}
	for (int i = l; i <= r; i++)
		a[i] = b[i];
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	mergesort(1, n);
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	return 0;
}
