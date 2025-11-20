#include <bits/stdc++.h>
using namespace std;

const int N = 150;
int n, flag = 1;
long long a[N][N], sum[N][N], summ, maxx;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			sum[i][j] = sum[i - 1][j] + (sum[i][j - 1] - sum[i - 1][j - 1]) + a[i][j]; //前i行j列所有元素的和
			//前(i - 1)行j列的和 + 第i行前(j - 1)个的和 + a[i][j]
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int p = 1; p <= i; p++) {
				for (int q = 1; q <= j; q++) {
					summ = sum[i][j] - sum[i][q - 1] - sum[p - 1][j] + sum[p - 1][q - 1]; //容斥原理，有一块被减了两次所以要加回来
					if (flag == 1) {
						flag = 0;
						maxx = summ;
					} else
						maxx = max(maxx, summ);
				}
			}
		}
	}
	cout << maxx << endl;
	return 0;
}