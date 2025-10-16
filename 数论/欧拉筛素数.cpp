#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000010;
int n, q, k;
int prime[maxn / 4], isprime[maxn], cnt, minpri[maxn], phi[maxn]; //cnt表示素数个数

void euler_sieve(int n) { //原理：只用一个数的最小素因数去标记它
	for (int i = 2; i <= n; i++)
		isprime[i] = 1; //初始化为1
	for (int i = 2; i <= n; i++) {
		if (isprime[i] == 1) {
			prime[++cnt] = i; //轮到i前它没被筛过，说明i是素数,并且可以看出prime里的素数是递增的
			minpri[i] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
			isprime[i * prime[j]] = 0; //把prime[j]的i倍筛掉
			minpri[i * prime[j]] = prime[j]; //最小素因子
			if (i % prime[j] == 0) { //说明prime[j]是i的最小素因数，也是(prime[j] * i)的最小素因数
				//记这个j为j0，那么之后的(prime[j] * i)的最小素因数也一定是prime[j0]，会在i更大的时候被prime[j0]筛掉，所以不用继续筛了
				phi[i * prime[j]] = phi[i] * prime[j]; //可以整除时，那么(i * prime[j])相比i没有增加新的素因子，由欧拉函数的计算公式可得
				break; //此时后半部分项数不变，只增加了n的大小，所以直接乘prime[j]即可
			} else //不能整除时，说明两者的gcd为1，新的phi可以直接将两者的相乘得到（也就是此时乘的是phi[prime[j] = (prime[j] - 1)）
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
		}
	}
}

int main() {
	int n;
	cin >> n;
	euler_sieve(n);
	return 0;
}
/*
比如 i = 12, prime[j] = 2时会直接跳出循环
因为例如后面的 12 * 3 = 36一定能在 i1 = 18, prime[j] = 2时被筛，后面的prime[j]都不用筛了

欧拉函数计算公式：phi(n) = n * (1 - 1 / p1) * (1 - 1 / p2) ... (1 - 1 / pk)，其中p1...pk为n的所有素因子
*/
