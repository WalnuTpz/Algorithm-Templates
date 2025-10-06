#include <bits/stdc++.h>
using namespace std;

int n, max0;
double a[20][3], dp[20][50010], minn = 10000010, dis[20][20];

//dp[i][k]表示当前走到i,状态为k的路径长度
//k看作n位二进制数，某一位为1表示走过这个点，反之没走过
double dist(double x, double y, double xx, double yy) {
	return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
}

int main() {
	scanf("%d", &n);
	max0 = (1 << n) - 1; //max0的二进制为n个1，表示所有点都走一遍的状态
	memset(dp, 127, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf", &a[i][1], &a[i][2]);
		dp[i][1 << (i - 1)] = dist(0, 0, a[i][1], a[i][2]);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++) {
			dis[i][j] = dist(a[i][1], a[i][2], a[j][1], a[j][2]);
			dis[j][i] = dis[i][j];
		}
	for (int k = 1; k <= max0; k++) {
		for (int i = 1; i <= n; i++) {
			if ((k & (1 << (i - 1))) == 0) //k的二进制第i位为0，说明当前状态不经过i，跳过
				continue;
			for (int j = 1; j <= n; j++) { //枚举上一个点j
				if (i == j) //跳过同一个点
					continue;
				if ((k & (1 << (j - 1))) == 0)
					continue;
				int k0 = k - (1 << (i - 1)); //上一个的状态,相当于把k的第i位变成0
				dp[i][k] = min(dp[i][k], dp[j][k0] + dis[i][j]);
			}
		}
	}
	for (int i = 1; i <= n; i++)
		minn = min(minn, dp[i][max0]);
	printf("%.2lf", minn);
	return 0;
}
