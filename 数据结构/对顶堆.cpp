#include <bits/stdc++.h>
using namespace std;

const int maxn = 100010;

int n, m, x, cnt;
string s;

priority_queue<int, vector<int>, greater<int>> pq1;
priority_queue<int> pq2;

void ins(int x) {
	if (pq2.empty() || x > pq2.top())
		pq1.push(x);
	else
		pq2.push(x);
	while (abs((int)pq1.size() - (int)pq2.size()) > 1) { //调整堆的大小
		if (pq1.size() > pq2.size()) {
			pq2.push(pq1.top());
			pq1.pop();
		} else {
			pq1.push(pq2.top());
			pq2.pop();
		}
	}
}

void query() {
	if ((pq1.size() + pq2.size()) % 2 == 0) //偶数长度，输出中间两个数的平均值
		cout << (pq1.top() + pq2.top()) / 2 << endl;
	else { //奇数长度，输出中间的数，即长度更大的那个堆的堆顶
		if (pq1.size() > pq2.size())
			cout << pq1.top() << endl;
		else
			cout << pq2.top() << endl;
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		ins(x);
	}
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> s;
		if (s[0] == 'a') {
			cin >> x;
			ins(x);
		} else
			query();
	}
	return 0;
}

/*
对顶堆通过维护一个小根堆pq1和一个大根堆pq2，保证pq1.top() >= pq2.top() （此时pq1的所有元素都大于pq2的所有元素）
并且 abs(pq1.size() - pq2.size()) <= 1，这样长度为奇数时，中位数就是较大的堆的堆顶，长度为偶数时，中位数就是两个堆顶的平均值。
在实际操作中，每次往对顶堆中插入一个数x，如果大于pq2.top()就加入pq1，反之加入pq2。为了维护size的差值 <= 1，所以当差值 > 1时，
要把多的那个堆的堆顶弹出并加入另一个堆，然后就完成了。
*/