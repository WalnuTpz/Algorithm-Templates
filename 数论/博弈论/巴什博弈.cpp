#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 200010;

int n, m;

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	if (n % (m + 1) != 0)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	return 0;
}

/*
一共n颗石头，两个人轮流取，可以取1~m个，取光石头的那个人赢，现在求先手有没有必胜策略
这里我们假设每个人都足够聪明（采取对自己最有利的方法，如果有必胜策略就一定会这么下）

(1) 0是必败态，因为它根本没法取石头
(2) 1/2/...m个，此时可以一次性取光，所以是必胜态
(3) (m + 1)个，不管自己怎么取都会转化为情况(2)（对方的必胜态），所以是必败态
(4) (m + 2)...(2m + 1)个，可以分别取1/2/...m转化为情况(3)（对面的必败态），所以是必胜态
后面的状态同理

综上，n % (m + 1) == 0时先手必败，反之先手必胜
*/
