#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int n, m, x, y, xx, yy, a[N][N], d[N][N];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> xx >> yy;
		d[x][y]++;
		d[x][yy + 1]--;
		d[xx + 1][y]--;
		d[xx + 1][yy + 1]++;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = a[i - 1][j] + (a[i][j - 1] - a[i - 1][j - 1]) + d[i][j];
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}