#include <bits/stdc++.h>
using namespace std;
const int N = 10000010;
int n, q, k;
int prime[N / 4], isprime[N], cnt, minpri[N]; //cnt表示素数个数

void euler_sieve(int n) { //原理：只用一个数的最小素因数去标记它
	for (int i = 2; i <= n; i++)
		isprime[i] = 1; //初始化为1
	for (int i = 2; i <= n; i++) {
		if (isprime[i] == 1) {
			prime[++cnt] = i; //轮到i前它没被筛过，说明i是素数,并且可以看出prime里的素数是递增的
			minpri[i] = i;
		}
		for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
			isprime[i * prime[j]] = 0; //把prime[j]的i倍筛掉
			minpri[i * prime[j]] = prime[j]; //最小素因子
			if (i % prime[j] == 0)
				break; //说明prime[j]是i的最小素因数，也是(prime[j] * i)的最小素因数
		}     		   //记这个j为j0，那么之后的(prime[j] * i)的最小素因数也一定是prime[j0]，会在i更大的时候被prime[j0]筛掉，所以不用继续筛了
	}
}

int main() {
	int n;
	scanf("%d", &n);
	euler_sieve(n);
	return 0;
}
/*
比如 i = 12, prime[j] = 2时会直接跳出循环
因为例如后面的 12 * 3 = 36一定能在 i1 = 18, prime[j] = 2时被筛，后面的prime[j]都不用筛了
*/
