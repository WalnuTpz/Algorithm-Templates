#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int q, op, i, x, heap[maxn], cnt;
int pos[maxn], id[maxn], m; // 插入ID->堆索引;   堆索引->插入ID;   总插入次数

void swap_heap(int a, int b) {
	swap(pos[id[a]], pos[id[b]]);
	swap(id[a], id[b]);
	swap(heap[a], heap[b]);
}

void up(int cur) { //向上交换操作
	while (cur > 1) { //还没到根节点，还能交换
		int fa = cur / 2;
		if (heap[fa] > heap[cur])
			swap_heap(fa, cur); //父亲比它大，那就交换
		else
			break; //否则就完成了
		cur = fa;
	}
}

void down(int cur) { //向下交换操作
	while (cur * 2 <= cnt) {
		int son = cur * 2;
		if (son + 1 <= cnt && heap[son + 1] < heap[son])
			son++; //看看是要左儿子还是右儿子跟它换（要和更小的那个换）
		if (heap[son] < heap[cur])
			swap_heap(cur, son); //儿子比它小，就交换
		else
			break; //否则就完成了
		cur = son;
	}
}

void push(int x) { //插入元素
	cnt++;
	m++;
	pos[m] = cnt;
	id[cnt] = m;
	heap[cnt] = x; //直接插到尾部
	up(cnt); // 从新插入的尾部节点开始向上交换
}

int top() { //返回根节点
	return heap[1];
}

void pop() { //删除最小值
	swap_heap(1, cnt); //将根节点和尾部节点交换
	cnt--; //并将尾节点删了
	down(1); // 从根节点开始向下交换
}

void decrease(int i, int x) { //减小第i次插入的元素
	int cur = pos[i];
	if (cur > cnt || cur < 1)
		return;
	heap[cur] = x;
	up(cur);  // 值变小了，需要向上交换
}

void increase(int i, int x) { //增大第i次插入的元素
	int cur = pos[i];
	if (cur > cnt || cur < 1)
		return;
	heap[cur] = x;
	down(cur); // 值变大了，需要向下交换
}


int main() {
	cin >> q;
	while (q--) {
		cin >> op;
		if (op == 1) {
			cin >> x;
			push(x);
		} else if (op == 2) {
			cout << top() << endl;
		} else if (op == 3) {
			pop();
		} else if (op == 4) {
			cin >> i >> x;
			decrease(i, x);
		} else if (op == 5) {
			cin >> i >> x;
			increase(i, x);
		}
	}
	return 0;
}

/*
本题实现了小根堆（大根堆只要把堆顶换成最大的就好了）
并且，STL 提供了优先队列这种数据结构，即 priority_queue，底层就是用堆实现的，
	头文件还是队列的 queue。优先队列有以下几种常用操作：
	priority_queue <int> q; 建立一个 int 类型的优先队列（大根堆）
	priority_queue <int, vector<int>, greater<int> > q; 建立一个小根堆
	q.top(); 查询最大（小）值。
	q.pop(); 弹出最大（小）值。
	q.push(x); 将 x 加入队列。

并且，这份代码还额外实现了增大某个元素和减小某个元素的操作
*/
