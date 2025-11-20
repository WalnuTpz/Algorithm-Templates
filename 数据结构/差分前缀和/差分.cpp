#include <bits/stdc++.h>
using namespace std;

const int N = 5000010;
int n, p, a[N], d[N], x, y, z, minn = 0x7fffff;

int main() {
	cin >> n >> p;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		d[i] = a[i] - a[i - 1]; //差分数组
	}
	for (int i = 1; i <= p; i++) {
		cin >> x >> y >> z;
		d[x] += z; //开头加上z，末尾的下一个减去z，相当于这一段加z
		d[y + 1] -= z;
	}
	for (int i = 1; i <= n; i++) {
		a[i] = a[i - 1] + d[i];
		minn = min(minn, a[i]);
	}
	cout << minn << endl;
	return 0;
}