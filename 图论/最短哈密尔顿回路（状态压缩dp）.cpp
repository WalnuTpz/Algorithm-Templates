#include <bits/stdc++.h>
using namespace std;

const double inf = 99999;
int n, m, max0, x, y, ans;
double d, minn = 1000010, dis[20][20];

struct node {
	int prej, prek;
	double dis;
} dp[20][50010];

//prej表示上一个点、prek表示上一个状态，用这两个变量实现递归查找路径
//k看作n位二进制数，某一位为1表示走过这个点，反之没走过
//dp[i][k].dis表示当前走到i,状态为k的路径长度

int find(int x0) { //寻找起点
	int x = x0, k = max0;
	while (dp[x][k].dis != 0) { //dp[x][k].dis == 0时表示找到了起点
		int x1 = dp[x][k].prej, k1 = dp[x][k].prek;
		x = x1, k = k1;
	}
	return x;
}

void print(int x0) { //打印具体路径
	printf("具体路径:");
	int x = x0, k = max0;
	while (dp[x][k].dis != 0) {
		printf("%c->", x - 1 + 'A');
		int x1 = dp[x][k].prej, k1 = dp[x][k].prek;
		x = x1, k = k1;
	}
	printf("%c->%c", x - 1 + 'A', x0 - 1 + 'A');
}

int main() {
	cin >> n >> m;

	max0 = (1 << n) - 1; //max0的二进制为n个1，表示所有点都走一遍的状态
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= max0; j++)
			dp[i][j].dis = inf;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dis[i][j] = inf;
	for (int i = 1; i <= n; i++) {
		dp[i][1 << (i - 1)].prej = i;
		dp[i][1 << (i - 1)].prek = 0;
		dp[i][1 << (i - 1)].dis = 0;
	}

	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> d;
		dis[x][y] = dis[y][x] = d;
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
				if (dp[j][k0].dis + dis[i][j] < dp[i][k].dis) {
					dp[i][k].prej = j; //记录上一个点
					dp[i][k].prek = k0; //记录上一个状态
					dp[i][k].dis = dp[j][k0].dis + dis[i][j];
				}
			}
			if (k == max0) { //状态为max0时，表示走完了，最后还要从终点回到起点
				int st = find(i); //寻找起点
				dp[i][max0].dis += dis[i][st];
			}
		}
	}
	//可以想象，整个图中的最短哈密尔顿回路去掉最长的边就可以变成整个图中的最短哈密尔顿路径
	//所以把每个点作为终点的最短哈密尔顿路径(dp[i][max0].dis)加上回到起点的距离(dis[i][st])再取最小值一定是整个图中的最短哈密尔顿回路

	for (int i = 1; i <= n; i++) {
		if (dp[i][max0].dis < minn) {
			minn = dp[i][max0].dis;
			ans = i; //更新答案
		}
	}
	cout << "最短路径长度:" << minn << endl;
	print(ans);
	return 0;
}

/*
10 17
1 2 2.7
1 8 3.4
1 9 2.4
2 3 2.6
2 9 2.1
3 4 2.9
3 5 4.2
3 10 3.3
4 5 2.2
4 6 2.1
4 7 5.3
5 6 4.4
6 10 2.5
7 8 1.7
7 10 3.2
8 9 1.8
9 10 2.8
*/