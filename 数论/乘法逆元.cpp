#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll a, mod;

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
	cin >> a >> mod;
	cout << inv(a) << endl;
	return 0;
}

/*
根据费马小定理，a^(p - 1) = 1 (mod p)，所以乘法逆元a^(-1) = a^(p - 1) / a = a^(p - 2)
*/
