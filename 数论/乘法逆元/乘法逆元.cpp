#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll a, mod, x, y;

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

ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) { //递归结束时an = gcd(a, b), bn = 0
		x = 1;
		y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, x, y);
	ll tmp = x;
	x = y;
	y = tmp - a / b * y;
	return d;
}

ll inv(ll a) { //只有mod是质数时才能用这个方法
	return fastpow(a, mod - 2);
}

ll inv2(ll a) { //mod与a互素时才可以用这个方法
	ll x, y;
	ll d = exgcd(a, mod, x, y);
	return (x % mod + mod) % mod;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> a >> mod;
	cout << inv(a) << endl;
	return 0;
}

/*
(1) 根据费马小定理，a^(p - 1) = 1 (mod p)，所以乘法逆元a^(-1) = a^(p - 1) / a = a^(p - 2)
但注意此时需要满足p是质数

(2) 对于a * x = 1 (% mod)，可以转化为a * x + mod * y = 1，那么就可以用exgcd(a, mod, x, y)来求出这个x，
但注意此时需要满足gcd(a, mod) = 1
*/
