#include <stdio.h>
#include <string.h>
char c[10], s0[10010], *s[100] *token;
int cnt;

int main() {
	scanf("%s %s", s0, c); //将s0根据c分割
	token = strtok(s0, c);
	while (token != NULL) {
		s[cnt++] = token; //s[i]指向token,相当于让它变成这个字符串
		token = strtok(NULL, c);
	}
	for (int i = 0; i < cnt; i++)
		printf("%s\n", s[i]);
	return 0;
}
