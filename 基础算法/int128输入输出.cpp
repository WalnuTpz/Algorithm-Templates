#include <bits/stdc++.h>
using namespace std;

using lll = __int128;

lll read128() {
	string s;
	cin >> s;  // 从标准输入读取一个字符串，代表一个整数（可能为负数）
	bool neg = false;
	int st = 0;
	if (s[0] == '-') { //处理负数情况
		neg = true;
		st = 1;
	}
	lll num = 0;
	for (int i = st; i < s.size(); i++) { // 将字符转换为对应数字并累加到结果中
		num = num * 10 + (s[i] - '0');
	}
	return neg ? -num : num; // 如果是负数，则结果取相反数
}

void print128(lll x) {
	if (x == 0) {
		cout << "0";
		return;
	}
	if (x < 0) { //处理负数情况
		cout << "-";
		x = -x;
	}
	string s;  // 用于存储每一位数字（逆序）
	while (x > 0) { // 将整数转为字符串（注意是从低位往高位推）
		s += (x % 10) + '0';
		x /= 10;
	}
	reverse(s.begin(), s.end()); //将字符串反转成正序
	cout << s;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	lll a, b, c;
	a = read128(),  b = read128();
	c = a * b;
	print128(c);
	return 0;
}
