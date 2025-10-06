#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int n, a[N], m, l, r;
long long sum[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> l >> r;
		cout << sum[r] - sum[l - 1] << endl;
	}
	return 0;
}