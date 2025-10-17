#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 100010;

int n, m, l, r, k, ans, a[maxn], lg[maxn], st[maxn][20];

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	lg[1] = 0;
	for (int i = 2; i <= n; i++)
		lg[i] = lg[i / 2] + 1;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		st[i][0] = a[i];
	}
	for (int j = 1; j <= lg[n]; j++)
		for (int i = 1; i <= n - (1 << j) + 1; i++)
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	for (int i = 1; i <= m; i++) {
		cin >> l >> r;
		k = lg[r - l + 1];
		ans = max(st[l][k], st[r - (1 << k) + 1][k]);
		cout << ans << endl;
	}
	return 0;
}

/*
st[i][j]表示以i为起点的长度为2^j的子串的最大值，很容易想到转移方程为st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1])
在每一次查询中，先找出2^k <= r - l + 1 < 2^(k + 1)的数k，即k = lg[r - l + 1]，那么可以将区间分为长为2^k并且可能有重叠的两段：
[l, l + 2^k - 1], [r - 2^k + 1, r]，这两段对应的st表中的值取max即可
*/
