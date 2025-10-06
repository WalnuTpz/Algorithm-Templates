#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll a, b, x, y;

ll exgcd(ll a, ll b) {
	if (b == 0) { //递归结束时an = gcd(a, b), bn = 0
		x = 1;
		y = 0;
		return a;
	}
	ll d = exgcd(b, a % b);
	ll tmp = x;
	x = y;
	y = tmp - a / b * y;
	return g;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> a >> b;
	ll d = exgcd(a, b);
	x = (x % b + b) % b;
	cout << x << endl;
	return 0;
}

/*
扩展欧几里得定理用于求解方程ax + by = gcd(a, b)的一组特解(x, y)，并能同时求出gcd(a, b)
*/
