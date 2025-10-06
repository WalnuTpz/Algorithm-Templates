#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 100010;

ll a, mod, fact[maxn], factinv[maxn];

ll fastpow(ll a, ll n) {
	ll ans = 1, base = a % mod;
	if (n == 0)
		return 1;
	if (base == 0)
		return 0;
	n = n % (mod - 1);
	while (n) {
		if (n & 1)
			ans = ans * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return ans;
}

ll inv(ll a) {
	return fastpow(a, mod - 2);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> mod;
	fact[1] = 1;
	for (int i = 2; i <= n; i++)
		fact[i] = fact[i - 1] * i % mod;
	factinv[n] = inv(fact[n]);
	for (int i = n - 1; i >= 1; i--)
		factinv[i] = factinv[i + 1] * (i + 1) % mod;
	for (int i = 1; i <= n; i++)
		cout << fact[i] << " " << factinv[i] << endl;
	return 0;
}

/*
快速求出所有阶乘的乘法逆元，首先求出1~n! (% mod)，然后直接求出n!的逆元。
接下来，因为factinv[i + 1] = (i + 1)!^(-1)，所以factinv[i + 1] * (i + 1) = i!^(-1) = factinv[i]
所以根据factinv[i] = factinv[i + 1] * (i + 1)倒过来递推求解即可
*/
