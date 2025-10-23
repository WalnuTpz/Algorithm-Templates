#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
using lll = __int128;
const int maxn = 20;

ll n, a[maxn], b[maxn], ans;

ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
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

ll inv(ll a, ll mod) { //因为a[i]不一定是质数，所以只能用exgcd来求逆元
	ll x, y;
	ll d = exgcd(a, mod, x, y);
	return (x % mod + mod) % mod;
}

ll crt() {
	lll mul = 1, ans = 0;
	for (int i = 1; i <= n; i++)
		mul *= a[i];
	for (int i = 1; i <= n; i++) {
		lll m = mul / a[i];
		ll invm = inv(m, a[i]);
		ans = (ans + b[i] * m * invm % mul) % mul;
	}
	return ans % mul;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i] >> b[i];
	ans = crt();
	cout << ans << endl;
	return 0;
}

/*
求方程组(i = 1 to n){x = b[i] (mod a[i])}的一个解

首先计算所有模数a[i]的乘积mul，然后令m = mul / a[i]，并求出它关于a[i]的逆元invm
最后答案ans = sum(i = 1 to n){b[i] * m * invm} % mul

证明：对于某个方程x = b[i] (mod a[i])，对于ans中除了i以外的数的贡献部分，因为它对应的m一定含有a[i]这个因子，所以这部分 % a[i]等于0，
对答案无影响，所以答案就等于i对ans的贡献，即b[i] * m * invm = b[i] * (m * invm) = b[i] (mod a[i])，所以这个方程成立。类比可得ans对于
所有方程都成立，所以它是原方程组的一个解
*/
