#include <bits/stdc++.h>
using namespace std;

int t, n, m, a[N], b[N], a1, a2;

int find(int x) {
	int l = 1, r = n, mid, ans;
	while (l <= r) {
		mid = (l + r) / 2;
		if (check(mid)) {
			r = mid - 1;
			ans = mid;
		} else
			l = mid + 1;
	}
	return ans;
}

int main() {

	return 0;
}