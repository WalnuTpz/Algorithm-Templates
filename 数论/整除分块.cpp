#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 200010;

int n;
ll ans;

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	ll l = 1, r; //初始左端点为1
	while (l <= n) {
		ll d = n / l; //对应的值为n / l
		r = n / d; //右端点为n / d
		ans += 1LL * (r - l + 1) * d;
		l = r + 1; //新的左端点为右端点加一
	}
	cout << ans << endl;
	return 0;
}

/*
普通整除分块计算的是 sum(i = 1 to n){floor(n / i)}，下面给出一种整除分块的变种及其计算方式：sum(i = 1 to n){floor(n / i) * i}
对比可以发现两者仅有项数差别，原来是(l - r + 1)个d，现在是(l + r) * (r - l + 1) / 2 个d也就是此时ans += (l + r) * (r - l + 1) / 2 * d，
其他部分的代码与普通整除分块相同
*/
