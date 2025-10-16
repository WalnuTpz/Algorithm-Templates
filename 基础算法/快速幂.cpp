#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll a, n, mod;

ll fastpow(ll a, ll n) {
	ll ans = 1, base = a % mod;
	if (n == 0)
		return 1;
	if (base == 0)
		return 0;
	//n = n % (mod - 1);
	while (n) {
		if (n & 1)
			ans = ans * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return ans;
}

ll fastpow2(ll a, ll n) {
	if (n == 0)
		return 1;
	if (a == 0)
		return 0;
	ll res = fastpow2(a, n / 2, mod);
	if (n % 2 == 1)
		return res * res % mod * a % mod;
	else
		return res * res % mod;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> a >> n >> mod;
	cout << fastpow(a, n) << endl;
	return 0;
}

/*
方法一：
用二进制的观点来理解快速幂，如a^11 = a^8 * a^2 * a^1，11 = (1011)_2
由于a^8,a^2这些数可以通过不断平方来快速计算，即base
所以只要b的当前二进制位为一，就让ans *= base，就可以快速计算

方法二：
设res = a^(n // 2) (//表示整除)
则n为奇数时a^n = res * res * a
则n为偶数时a^n = res * res

进一步优化快速幂：
(1)在a过大时让base = a % mod，而不是直接等于a
(2)在n过大时让n = n % (mod - 1)，因为根据费马小定理，a^(mod - 1) = 1 (在模mod的时候)，
所以指数n关于mod的循环节为(mod - 1)，所以可以模mod
*/
