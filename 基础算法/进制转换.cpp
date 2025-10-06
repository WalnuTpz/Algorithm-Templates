#include <bits/stdc++.h>
using namespace std;

int k1, k2;
string s;

int ctoi(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 36;
}

char itoc(int i) {
	if (i < 10)
		return i + '0';
	if (i < 36)
		return i - 10 + 'A';
	if (i < 62)
		return i - 36 + 'a';
}

void solve() {
	cin >> k1 >> k2 >> s; //一个k1进制的数s直接转换为k2进制
	cout << k1 << " " << s << endl << k2 << " ";
	int l = s.size();
	vector<int> a(l, 0), b;
	for (int i = 0; i < l; i++) //字符转换为数值
		a[i] = ctoi(s[i]);
	while (a.size() > 0) { //将s不断在k1进制下除以k2
		int l = a.size();
		vector<int> tmp(l, 0); //除完后的结果
		int jw = 0; //进位
		for (int i = 0; i  < l; i++) {
			int numb = a[i] + jw * k1; //当前位 + 进位 * k1
			tmp[i] = numb / k2;
			jw = numb % k2;
		}
		a = tmp;
		b.push_back(jw); //结果添加最终的余数
		while (a.size() > 0 && a[0] == 0)
			a.erase(a.begin());
	}
	for (int i = b.size() - 1; i >= 0; i--) //反方向输出答案，输出时要把数值转换为字符
		cout << itoc(b[i]);
	cout << endl << endl;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
		solve();
	return 0;
}
