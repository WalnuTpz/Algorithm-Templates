#include <bits/stdc++.h>
using namespace std;

int n;

int read() {
	int fh = 1, res;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fh = -1;
	res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return fh * res;
}

void write(int x) {
	if (x < 0)
		putchar('-'), x = -x;
	if (x < 10)
		putchar(x + '0');
	else
		write(x / 10), putchar(x % 10 + '0');
}

int main() {
	n = read(); //scanf("%d", &n)
	write(n); //printf("%d", n)
	return 0;
}
