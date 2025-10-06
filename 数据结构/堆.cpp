#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int n, op, x, heap[N], cnt;

void push(int x) { //插入元素 x
	cnt++;
	heap[cnt] = x;  //直接插到尾部
	int now = cnt;
	while (now > 1) { //还没到根节点，还能交换
		int fa = now / 2; //找到它的父亲
		if (heap[fa] > heap[now])
			swap(heap[fa], heap[now]); //父亲比它大，那就交换
		else
			break; //如果比它父亲小，那就代表着插入完成了
		now = fa; //交换
	}
}

int top() { //返回根节点
	return heap[1];
}

void pop() { //弹掉最小值
	swap(heap[1], heap[cnt]); //将根节点和尾部节点交换并将尾节点删了
	cnt--;
	int now = 1;
	while (now * 2 <= cnt) { //对该节点进行向下交换的操作
		int nxt = now * 2; //找出当前节点的左儿子
		if (nxt + 1 <= cnt && heap[nxt + 1] < heap[nxt])
			nxt++; //看看是要左儿子还是右儿子跟它换（要和更小的那个换）
		if (heap[nxt] < heap[now])
			swap(heap[now], heap[nxt]); //如果不符合堆性质就换
		else
			break; //否则就完成了
		now = nxt; //往下一层继续向下交换
	}
}

int main() {
	cin >> n;
	while (n--) {
		cin >> op;
		if (op == 1) {
			cin >> x;
			push(x);
		}
		if (op == 2)
			cout << top() << endl;
		if (op == 3)
			pop();
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
*/
