#include <stdio.h>
#include <stdlib.h>
int a[10], n = 5;
char **s;

int cmp1(const void *i, const void *j) { //升序
	return *((int *)i) - *((int *)j);
}

int cmp2(const void *i, const void *j) { // 降序
	return *((int *)j) - *((int *)i);
}

int strcmp(const void *i, const void *j) {
	return strcmp(*(char **)i, *(char **)j);
}

int main() {
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	qsort(a + 1, n, sizeof(int), cmp1);
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);

	s = (char **)malloc(110 * sizeof(*s));
	for (int i = 0; i < 100; i++)
		s[i] = (char *)malloc(110 * sizeof(*s[i]));
	for (int i = 0; i < n; i++)
		scanf("%s", s[i]);
	qsort(s, n, sizeof(s[0]), cmp2);
	return 0;
}

/*

//使用文中函数进行二维数组排序
int cmp(const void *a, const void *b) {
	return ((int *)a)[0] - ((int *)b)[0];
}

int main() {
	int arr[3][3] = { 3, 1, 5, 9, 7, 6, 4, 8, 0};

	size_t num = sizeof(arr) / sizeof(arr[0][0]);
	size_t sz = sizeof(arr[0][0]);

	qsort(arr, num, sz, cmp);
	int i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", arr[i][j]);
		}
	}

	return 0;
}
*/