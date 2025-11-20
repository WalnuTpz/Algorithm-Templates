#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 3000010;

ll n, p, inv[maxn];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> p;
	inv[1] = 1;
	cout << inv[1] << endl;
	for (int i = 2; i <= n; i++) {
		inv[i] = (p - p / i) * inv[p % i] % p;
		cout << inv[i] << "\n";
	}
	return 0;
}

/*
这个算法可以递推求出1~n所有数字的乘法逆元，而不是每个数单独求。
初始条件为1^(-1) = 1 (mod p)
然后对于2 <= i <= n，设p = k * i + r, k = i / p, r = i % p，则有k * i + r = 0 (mod p)
两边同乘(i^(-1) * r^(-1))，则有k * r^(-1) + i^(-1) = 0 (mod p)
则有i^(-1) = -k * r^(-1) = -(i / p) * r^(-1) = (p - i / p) * r^(-1) (mod p)
*/
