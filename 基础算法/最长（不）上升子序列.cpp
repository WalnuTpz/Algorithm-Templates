#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 100010;

int n, x, a[maxn];
ll ans1, ans2, dp1[maxn], dp2[maxn];

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	while (cin >> x)
		a[++n] = x;
	dp1[1] = dp2[1] = a[1]; //dp1单调不递增（递减或相等），dp2单调递增
	ans1 = ans2 = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i] <= dp1[ans1])
			dp1[++ans1] = a[i];
		else {
			int pos = upper_bound(dp1 + 1, dp1 + ans1 + 1, a[i], greater<int>()) - dp1;
			dp1[pos] = a[i];
		}

		if (a[i] > dp2[ans2])
			dp2[++ans2] = a[i];
		else {
			int pos = lower_bound(dp2 + 1, dp2 + ans2 + 1, a[i]) - dp2;
			dp2[pos] = a[i];
		}
	}
	cout << ans1 << endl;
	cout << ans2 << endl;
	return 0;
}

/*
这里使用一种巧妙的方法，我们只介绍dp1，而dp2同理。这里我们用dp1维护当前最长不上升子序列的最优情况，然后将a中的每个元素逐个插入。
首先如果a[i] <= dp1[ans1]，说明它小于当前最长不上升子序列中的所有元素，所以直接插到尾部，并且答案加一；
反之，使用upper_bound + greater<int>()找到dp1中第一个满足dp1[pos] < a[i]的位置pos，此时将它替换成a[i]，这样相当于抬高这个位置，
使得后续元素更容易插入（因为当前最长不上升子序列中的每个元素越高，那么新的元素就越容易插入到尾部，答案也就越大）

然后对于dp2，此时要找到的是第一个满足dp2[pos] >= a[i]的位置pos，把它拉低，其他同上
*/