#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 200010;

ll a, m, b, pm, ans, flag;

ll modread(ll mod) {
	ll fh = 1, res;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fh = -1;
	res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') {
		res = res * 10 + c - '0';
		if (res >= mod)
			flag = 1;
		res %= mod;
	}
	return res;
}

ll phi(ll n) {
	ll ans = n;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i == 0)
			ans -= ans / i;
		while (n % i == 0)
			n /= i;
	}
	if (n > 1)
		ans -= ans / n;
	return ans;
}

ll fastpow(ll a, ll n) {
	ll ans = 1, base = a % m;
	if (n == 0)
		return 1;
	if (base == 0)
		return 0;
	while (n) {
		if (n & 1)
			ans = ans * base % m;
		base = base * base % m;
		n >>= 1;
	}
	return ans;
}

int main() {
	cin >> a >> m;
	pm = phi(m);
	b = modread(pm);
	if (flag) //b >= phi(m)
		b += pm;
	ans = fastpow(a, b);
	cout << ans << endl;
	return 0;
}

/*
基础欧拉定理：若gcd(a, m) = 1，那么a^b = a^(b % phi(m)) (mod m)
（并且此时还有一个重要定理a^phi(m) = 1）

扩展欧拉定理：若gcd(a, m) > 1
(1)若b < phi(m)，a^b = a^b (mod m) （此时指数较小，无需降低指数）
(2)若b >= phi(m)，a^b = a^(b % phi(m) + phi(m)) (mod m)
*/