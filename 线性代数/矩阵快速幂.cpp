#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 110, mod = 1e9 + 7;

int n;
ll k, a[maxn][maxn], base[maxn][maxn], ans[maxn][maxn];

void mul(ll a[maxn][maxn], ll b[maxn][maxn]) {
	ll c[maxn][maxn] = {0};
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = c[i][j];
}

void fastpow(ll ans[maxn][maxn], ll a[maxn][maxn], ll k) {
	ll base[maxn][maxn];
	for (int i = 1; i <= n; i++) {
		ans[i][i] = 1; //ans一开始是单位矩阵
		for (int j = 1; j <= n; j++)
			base[i][j] = a[i][j];
	}
	while (k) {
		if (k & 1)
			mul(ans, base);
		mul(base, base);
		k >>= 1;
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> a[i][j];
	fastpow(ans, a, k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << ans[i][j] << " ";
		cout << endl;
	}
	return 0;
}

/*
注意：矩阵快速幂中不能使用k %= (mod - 1)这个语句，因为费马小定理只适用于整数乘法，但不适用于矩阵乘法。
详细来说是因为这个结论是基于群论中的一个概念：循环群。在模 p 意义下的整数乘法构成一个群，并且这个群的阶是 p-1；
但矩阵乘法在模 p 意义下，不一定构成一个群。
*/
