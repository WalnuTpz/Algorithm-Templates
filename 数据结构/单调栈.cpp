#include <bits/stdc++.h>
using namespace std;

const int N = 3000010;
int n, a[N], r[N];
stack<int> st;

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = n; i >= 1; i--) {
		while (!st.empty() && a[st.top()] <= a[i]) //因为要找大于它的第一个元素，所以这里是小于等于
			st.pop();
		r[i] = (st.empty() ? 0 : st.top()); //右侧大于它的第一个元素的下标
		st.push(i);
	}
	for (int i = 1; i <= n; i++)
		cout << r[i] << " ";
	return 0;
}

