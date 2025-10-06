#include <bits/stdc++.h>
using namespace std;

const int maxa = 1000010;
int n;

int prime[maxa / 4], isprime[maxa], cnt, minpri[maxa];

void euler_sieve(int n) {
	for (int i = 2; i <= n; i++)
		isprime[i] = 1;
	for (int i = 2; i <= n; i++) {
		if (isprime[i] == 1) {
			prime[++cnt] = i;
			minpri[i] = i;
		}
		for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
			isprime[i * prime[j]] = 0;
			minpri[i * prime[j]] = prime[j];
			if (i % prime[j] == 0)
				break;
		}
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	euler_sieve(maxa - 10);
	cin >> n;
	vector<int> ans;
	int tmp = n, cur = minpri[tmp]; //cur表示当前数的最小质因数
	while (tmp > 1) {
		ans.push_back(cur);
		while (tmp > 1 && tmp % cur == 0) { //tmp的因子里除去所有cur
			tmp /= cur;
			cnt++;
		}
		cur = minpri[tmp]; //新的cur等于新的tmp的最小质因数
	}
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
	return 0;
}