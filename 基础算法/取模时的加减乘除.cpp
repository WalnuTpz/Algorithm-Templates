#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int a, b;

int add(int x, int y) { //加法
	x += y;
	if (x >= mod)
		x -= mod;
	if (x < 0)
		x += mod;
	return x;
}

int sub(int x, int y) { //减法
	return add(x, -y);
}

int mul(int x, int y) { //乘法
	return x * 1LL * y % mod;
}

int fastpow(int x, int y) { //快速幂
	int z = 1;
	while (y) {
		if (y & 1)
			z = mul(z, x);
		x = mul(x, x);
		y >>= 1;
	}
	return z;
}

int divide(int x, int y) { //除法，并且由于div已经是关键字了，所以用换成divide
	return mul(x, fastpow(y, mod - 2));
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> a >> b;
	cout << add(a, b) << endl;
	cout << sub(a, b) << endl;
	cout << mul(a, b) << endl;
	cout << divide(a, b) << endl;
	return 0;
}