#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 10010;
const double inf = 1e12, eps = 1e-9;

int n;
double a[maxn], b[maxn], c[maxn];

double f(double x) {
	double ans = -inf;
	for (int i = 1; i <= n; i++)
		ans = max(ans, a[i] * x * x + b[i] * x + c[i]);
	return ans;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i] >> b[i] >> c[i];
	double l = 0, r = 1000, mid1, mid2, ans = inf;
	while (r - l > eps) {
		mid1 = l + (r - l) / 3;
		mid2 = l + (r - l) * 2 / 3;
		if (f(mid1) > f(mid2))
			l = mid1;
		else
			r = mid2;
	}
	cout << fixed << setprecision(4) << f(l) << endl;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
		solve();
	return 0;
}
