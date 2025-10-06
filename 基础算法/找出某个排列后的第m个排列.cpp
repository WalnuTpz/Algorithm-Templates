#include <bits/stdc++.h>
using namespace std;
int n, m, a[10010], b[10010], cnt, flag;

void dfs(int num) {
	if (flag == 1)
		return; //已经结束了，剪枝
	if (num == n + 1) {
		cnt++;
		if (cnt == m + 1) { //到达初始状态时cnt也加一，所以最终cnt为 m + 1
			for (int i = 1; i <= n; i++)
				printf("%d ", a[i]);
			flag = 1;
		}
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (flag == 1)
			break; //已经结束了，剪枝
		if (cnt == 0)
			i = a[num]; //通过将i指定为题目中给出的那个数
		if (b[i] == 0) {//从而快速建立初始的递归状态
			b[i] = 1;
			a[num] = i;
			dfs(num + 1);
			b[i] = 0;
			a[num] = 0;
		}
	}
}

/*
上面这段程序相当于用dfs手动实现next_permutation (全排列中的下一个排列)

for (int i = 1; i <= m; i++)
	next_permutation(a + 1, a + n + 1);
for (int i = 1; i <= n; i++)
	printf("%d ", a[i]);

*/
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	dfs(1);
	return 0;
}
