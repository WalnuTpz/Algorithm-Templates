#include <bits/stdc++.h>
using namespace std;

char s[4][10010], c;
int n, a[4][10010];

void longscanf(int a[], char s[]) { //读入高精度数
	scanf("%s", s);
	a[0] = strlen(s);
	for (int j = 1; j < a[0]; j++)
		a[j] = int(s[a[0] - j] - '0'); //读入s为4321，在a中储存为1234（从低位往高位存储）
}

void longturn(int a[], int b) { //把整数b转换为高精度数a
	int n = 0; //高精度数第零位表示长度，第一位往后是它的数值
	while (b != 0) {
		a[++n] = b % 10;
		b /= 10;
	}
	a[0] = n;
}

void longcopy(int a[], int b[]) { //拷贝高精度数 (a = b)
	for (int i = 0; i <= b[0]; i++)
		a[i] = b[i];
}

void longprint(int a[]) { //打印高精度数 (print(a))
	if (a[a[0]] == 0)
		a[0] = 1; //防止输出0时输出000等情况
	for (int i = a[0]; i >= 1; i--)
		printf("%d", a[i]);
	printf("\n");
}

int longcmp(int a[], int b[]) { //比较高精度数大小
	if (a[0] > b[0])
		return 1;
	if (a[0] < b[0])
		return 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] > b[i])
			return 1;
		if (a[i] < b[i])
			return 0;
	}
	return 0;
}

void longadd(int a[], int b[]) { //高精度加法 (a += b)
	int len, i = 0;
	len = max(a[0], b[0]);
	while (i <= len or a[len] > 9) {
		i++;
		a[i] += b[i];
		if (i > 1) {
			a[i] += a[i - 1] / 10;
			a[i - 1] %= 10;
		}
		if (i == len && a[len] > 9)//进位
			len++;
	}
	a[0] = len;
}

void longsub(int a[], int b[]) { //高精度减法
	int len, i = 0;
	if (a[0] > b[0])
		len = a[0];
	else
		len = b[0];
	while (i <= len) {
		i++;
		a[i] -= b[i];
		if (a[i] < 0 ) { //借位
			a[i] += 10;
			a[i + 1]--;
		}
	}
	while (a[len] == 0) //处理数字前面的0
		len--;
	a[0] = len;
}

void longmult(int a[], int b[]) { //高精度乘法 (a *= b)
	int c[10000] = {0}; //根据题目要求开c的大小
	c[0] = a[0] + b[0] - 1;
	for (int i = 1; i <= a[0]; i++) {
		for (int j = 1; j <= b[0]; j++) {
			c[i + j - 1] += a[i] * b[j];
			if (i + j - 1 > 1) {
				c[i + j - 1] += c[i + j - 2] / 10;
				c[i + j - 2] %= 10;
			}
		}
	}
	while (c[c[0]] > 9) {//进位
		c[0]++;
		c[c[0]] = c[c[0] - 1] / 10;
		c[c[0] - 1] %= 10;
	}
	longcopy(a, c);
}

void longreverse(int a[], int b[]) { //高精度数反转(用来做除法)
	a[0] = b[0];
	for (int i = 1; i <= a[0]; i++) {
		a[i] = b[a[0] - i + 1];
	}
}

void longdiv(int a[], int b[]) { //高精度除法
	int a1[10000] = {0}, b1[10000] = {0}, c1[10000] = {0}, j, k;
	longreverse(a1, a);
	longreverse(b1, b);
	c1[0] = a1[0] - b1[0] + 1;
	for (int i = 1; i <= c1[0]; i++) {//是把除法转换成减法，不停地减，每减一次，对应位置的答案加一
		while (1) {
			for (j = i, k = 1; j <= b1[0] + i - 1, k <= b1[0]; j++, k++)
				if (a1[j] > b1[k]) {//如果被除数的某位置先比除数大了，则可以做减法，跳出循环
					j = b1[0] + 1;
					break;
				} else if (a1[j] < b1[k])//如果被除数的某位置先比除数小了，则不可做减法，跳出循环
					break;
			//若两数相同，则继续循环判断
			if (j > b1[0]) { //下面是高精度减法
				for (j = b1[0] + i - 1, k = b1[0]; j >= i, k >= 1; j--, k--)
					if (a1[j] - b1[k] >= 0)
						a1[j] -= b1[k];
					else
						a1[j] += 10, a1[j - 1]--, a1[j] -= b1[k];
				c1[i]++;
			} else {//如果不能做减法
				a1[i + 1] += a1[i] * 10;//将最前一位的所有数全部退到下一位置的数上
				a1[i] = 0;
				break;
			}
		}
	}
	longreverse(a, c1);
}

int main() {
	scanf("%d", &n);
	getchar();
	for (int i = 1; i <= n; i++) {
		scanf("%s %c %s", s[1], &c, s[2]);
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 10001; j++) //每次做完后memset, 防止上一次的数未被覆盖的部分对本次运算产生影响
				a[i][j] = 0;
			a[i][0] = strlen(s[i]);
			for (int j = a[i][0] - 1; j >= 0; j--)
				a[i][a[i][0] - j] = s[i][j] - '0';
		}
		if (c == '+')
			longadd(a[1], a[2]);
		if (c == '-')
			longsub(a[1], a[2]);
		if (c == '*')
			longmult(a[1], a[2]);
		if (c == '/')
			longdiv(a[1], a[2]);
		longprint(a[1]);
	}
	return 0;
}
