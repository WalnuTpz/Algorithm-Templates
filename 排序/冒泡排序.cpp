#include <bits/stdc++.h>
using namespace std;
int n, a[10010], tmp;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n - i + 1; j++) {
			if (a[j] > a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	return 0;
}
