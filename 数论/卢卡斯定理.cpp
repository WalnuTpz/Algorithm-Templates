#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 100010;

ll n, m, p, fact[maxn];

ll fastpow(ll a, ll n) {
	ll ans = 1, base = a % p;
	if (n == 0)
		return 1;
	if (base == 0)
		return 0;
	while (n) {
		if (n & 1)
			ans = ans * base % p;
		base = base * base % p;
		n >>= 1;
	}
	return ans;
}

ll C(ll n, ll m) {
	if (n < m)
		return 0;
	return fact[n] * fastpow(fact[m], p - 2) * fastpow(fact[n - m], p - 2) % p;
}

ll lucas(ll n, ll m) {
	if (n < p && m < p)
		return C(n, m) % p;
	else
		return C(n % p, m % p) * 1LL * lucas(n / p, m / p) % p;
}

void solve() {
	cin >> n >> m >> p;
	fact[0] = 1;
	for (int i = 1; i <= p; i++)
		fact[i] = fact[i - 1] * i % p;
	cout << lucas(n + m, n) << endl;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
		solve();
	return 0;
}

/*
lucas定理：C(n, m) % p = C(n % p, m % p) * C(n / p, m / p) % p     证明可以用二项式定理，这里省略了
第一项由于两个数都已经 < p，所以可以直接计算，第二项可以继续使用lucas定理递归计算

有一些需要注意的点：(1)由于本题是带取模的组合数，所以不能用公式直接计算，而是预处理阶乘然后用阶乘和乘法逆元来计算
(2)计算组合数时，注意特判n < m时直接返回0（因为式子的第一项取模以后n, m的大小关系可能会改变）
*/