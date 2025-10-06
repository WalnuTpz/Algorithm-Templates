#include <bits/stdc++.h>
using namespace std;
int n, a[10010], tmp, minn;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) {
		minn = i;
		for (int j = i + 1; j <= n; j++) {
			if (a[j] < a[minn])
				minn = j;
		}
		tmp = a[i];
		a[i] = a[minn];
		a[minn] = tmp;
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	return 0;
}
