#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N = 10010;
const ull base = 131, prime = 233317, mod = 212370440130137957ll;
ull n, a[N], cnt = 1;
string s;

ull hashe(string s) {
	int l = s.size();
	ull ans = 0;
	for (int i = 0; i < l; i++)
		ans = (ans * base + (ull)s[i]) % mod + prime;
	return ans;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		a[i] = hashe(s);
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i < n; i++)
		if (a[i] != a[i + 1]) //字符串不重复
			cnt++;
	cout << cnt << endl;
	return 0;
}

/*
另一种方法：
	set<string> st;
	st.insert(s);
	cout<<st.size();
*/