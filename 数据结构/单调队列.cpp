#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000010;

int n, k, a[maxn];

deque<int> dq;

int judge(int a, int b, int flag) { //判断函数
	if (flag == 1)
		return a >= b;
	else
		return a <= b;
}

void solve(int flag) {
	deque<int> dq; //因为需要队首队尾两侧出队，所以使用双端队列
	vector<int> m;
	for (int i = 1; i <= k; i++) {
		while (!dq.empty() && judge(a[i], dq.back(), flag))
			dq.pop_back();
		dq.push_back(a[i]);
	}
	m.push_back(dq.front());
	for (int i = 1; i <= n - k; i++) {
		if (dq.front() == a[i])
			dq.pop_front();
		while (!dq.empty() && judge(a[i + k], dq.back(), flag))
			dq.pop_back();
		dq.push_back(a[i + k]);
		m.push_back(dq.front());
	}
	for (auto x : m)
		cout << x << " ";
	cout << endl;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	solve(0); //flag = 0，此时需要把 >= a[i]的元素都从队尾出队
	solve(1);
	return 0;
}

/*
单调队列就是一个里面的元素都是单调的队列，并且它队首队尾都可以出队，可以用于统计滑动窗口最值。假如求的是最小值，考虑这样一个事实：
当滑动窗口统计到某个元素时，如果这个元素 <= 它前面的元素，那它更容易成为当前窗口的最小值，所以它可以留在队列里，并且把前面 >= s它
的元素都从队尾出队（因为那些元素已经一定不可能成为当前窗口的最小值了），所以可以看出此时队列里的元素是单调递增的，所以窗口最小值
就是队首元素。然后又因为队列中元素的下标是递增的，所以窗口向后滑动时如果队首元素是当前窗口需要抛弃的元素，就把它从队首出队，
然后这道题就做完了。对于窗口最大值，只需要把 <= a[i]的元素都从队尾出队即可
*/
