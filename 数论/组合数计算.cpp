#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 110;
int n, m;
ll c[N][N], ans;

ll C(ll n, ll m) {
	ll ans = 1;
	for (ll i = 1; i <= m; ++i) {
		ans *= n - i + 1;
		ans /= i;
	}
	return ans;
}

int main() {
	cin >> n >> m;
	c[0][0] = 1;
	for (int i = 1; i <= 100; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
			c[i][j] = c[i][j - 1] + c[i - 1][j - 1];
	}
	cout << c[n][m] << endl; //递推求解
	cout << C(n, m) << endl; //直接计算
	return 0;
}