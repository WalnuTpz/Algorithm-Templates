#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll a, b, c, x, y;

ll exgcd(ll a, ll b) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll d = exgcd(b, a % b);
	ll tmp = x;
	x = y;
	y = tmp - a / b * y;
	return d;
}

void solve() {
	cin >> a >> b >> c;
	ll d = exgcd(a, b);
	if (c % d != 0) {
		cout << -1 << endl;
		return;
	}
	ll x0 = x * c / d, y0 = y * c / d;
	ll dx = b / d, dy = a / d;
	ll kmin = ceil((1.0 - x0) / dx), kmax = floor((y0 - 1.0) / dy);
	if (kmax >= kmin) {
		ll cnt = kmax - kmin + 1;
		ll xmax = x0 + kmax * dx, xmin = x0 + kmin * dx;
		ll ymax = y0 - kmin * dy, ymin = y0 - kmax * dy;
		cout << cnt << " " << xmin << " " << ymin << " " << xmax << " " << ymax << endl;
	} else {
		ll xmin = x0 + kmin * dx, ymin = y0 - kmax * dy;
		cout << xmin << " " << ymin << endl;
	}

}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int T;
	cin >> T;
	while (T--)
		solve();
	return 0;
}

/*
先根据扩展欧几里得定律求出 ax + by = gcd(a, b)的一组特解(x, y)，同时求出d = gcd(a, b)，那么对于原方程 ax + by = c，也存在一组特解
(x0, y0) = (x * c / d, y * c / d)，那么通解则为 a(x0 + tb) + b(y0 - ta) = c，此时需要满足tb, ta都是整数，所以t一定是(1 / d)的倍数，
那么令dx = b / d, dy = a / d，则有 t = (1 / d) * k，a(x0 + k * dx) + b(y0 - k * dy) = c，可以看出k越大时x越大，y越小。
假如需要让x >= 1,y >= 1，那么一定有 x0 + k * dx >= 1, y0 - k * dy >= 1，所以kmin = ceil((1.0 - x0) / dx), kmax = floor((y0 - 1.0) / dy)，
此时满足题意的kmin <= k <= kmax，最后进行分类讨论

(1)若c % d != 0，说明原方程无整数解
(2)若kmin <= kmax，那么存在正整数解，kmin对应xmin, ymax，kmax对应xmax, ymin，并且正整数解的数量cnt = kmax - kmin + 1
(3)若kmin > kmax，那么不存在正整数解，kmin对应xmin，kmax对应ymin
*/

