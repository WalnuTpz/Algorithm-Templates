#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	vector<int> ans;
	cin >> n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			while (n % i == 0) //及时减小i，使后续减少枚举范围
				n /= i;
			ans.push_back(i);
		}
	}
	for (auto x : ans)
		cout << x << " ";
	cout << endl;
	return 0;
}
