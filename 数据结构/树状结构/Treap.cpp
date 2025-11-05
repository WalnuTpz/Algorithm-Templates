#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
const int maxn = 100010, inf = 2147483647;

int num, root;

struct node {
	int val, ls, rs, cnt, siz;
	//值，左孩子下标，右孩子下标，出现次数，子树大小（包含该节点大小）
	int rnd; //随机优先级，用于维护堆性质
} t[maxn];

void pushup(int x) { //更新该节点的siz
	t[x].siz = t[t[x].ls].siz + t[t[x].rs].siz + t[x].cnt;
}

void lrotate(int &x) { //左旋
	int cur = t[x].rs; //cur 是 x 的右孩子
	t[x].rs = t[cur].ls; //x 的新右孩子是 cur 的左孩子
	t[cur].ls = x; //cur 的新左孩子是 x
	t[cur].siz = t[x].siz; //cur 继承 x 的 siz
	pushup(x); //更新 x (现在是 cur 的左孩子) 的 siz
	x = cur; //父节点指向 x 的指针现在指向 cur
}

void rrotate(int &x) { //右旋
	int cur = t[x].ls; //cur 是 x 的左孩子
	t[x].ls = t[cur].rs; //x 的新左孩子是 cur 的右孩子
	t[cur].rs = x; //cur 的新右孩子是 x
	t[cur].siz = t[x].siz; //cur 继承 x 的 siz
	pushup(x); //更新 x (现在是 cur 的右孩子) 的 siz
	x = cur; //父节点指向 x 的指针现在指向 cur
}

void add(int &x, int v) { //插入某一个数 (Treap 版本)
	if (x == 0) { //节点不存在，添加节点
		num++;
		x = num;
		t[x].val = v;
		t[x].cnt = 1;
		t[x].siz = 1;
		t[x].rnd = rand(); //赋予随机优先级
		return;
	}
	if (v == t[x].val) { //已经有这个数，只需把次数加一
		t[x].cnt++;
	} else if (v < t[x].val) { //v < t[x].val，说明v在x的左子树里
		add(t[x].ls, v); //继续递归
		if (t[t[x].ls].rnd < t[x].rnd) //破坏了堆性质 (子<父)
			rrotate(x); //右旋
	} else { //v > t[x].val，说明v在x的右子树里
		add(t[x].rs, v); //继续递归
		if (t[t[x].rs].rnd < t[x].rnd) //破坏了堆性质
			lrotate(x); //左旋
	}
	pushup(x); //在递归返回时更新 siz
}

void remove(int &x, int v) { //删除某一个数（只将它的出现次数减小1）
	if (x == 0)
		return; //没有找到
	if (v == t[x].val) { //已经找到v，进行删除操作
		if (t[x].cnt > 1) { //出现次数 > 1
			t[x].cnt--; //出现次数减一
			pushup(x);
			return;
		}
		//如果删除后出现次数为0，则需要把该节点删去
		if (t[x].ls == 0 || t[x].rs == 0) { //没有左右孩子或只有一边孩子
			x = t[x].ls + t[x].rs; //返回存在的孩子（或0）作为新的根
		} else if (t[t[x].ls].rnd < t[t[x].rs].rnd) { //左孩子优先级高 (rnd小)
			rrotate(x); //右旋，将 x 旋下去
			remove(t[x].rs, v); //继续在 x 的(新)右子树中删除 v
			pushup(x); //更新 siz
		} else { //右孩子优先级高
			lrotate(x); //左旋
			remove(t[x].ls, v); //继续在 x 的(新)左子树中删除 v
			pushup(x); //更新 siz
		}
	} else if (v < t[x].val) { //v < t[x].val，说明v在x的左子树里，递归删除
		remove(t[x].ls, v);
		if (x != 0)
			pushup(x); //更新该节点的siz
	} else { //v > t[x].val，说明v在x的右子树里，递归删除
		remove(t[x].rs, v);
		if (x != 0)
			pushup(x); //更新该节点的siz
	}
}

int querymin(int x) { //查询最小值
	if (t[x].ls == 0)
		return t[x].val;
	else //一直往左子树查找
		return querymin(t[x].ls);
}

int querymax(int x) { //查询最大值
	if (t[x].rs == 0)
		return t[x].val;
	else //一直往右子树查找
		return querymax(t[x].rs);
}

int search(int x, int v) { //查找某一个数是否存在
	if (v == t[x].val) //找到了
		return 1;
	else if (v < t[x].val) //v < t[x].val，往左子树继续查找
		return search(t[x].ls, v);
	else //v > t[x].val，往右子树继续查找
		return search(t[x].rs, v);
}

void travel(int x) { //中序遍历整棵树
	if (x == 0)
		return;
	travel(t[x].ls);
	cout << t[x].val << " ";
	travel(t[x].rs);
}

int querylst(int x, int v, int ans) { //查找某个数的前序
	//ans表示目前查找到的小于v的数的最大值
	if (x == 0)
		return ans; //没找到，返回上一层的ans
	if (t[x].val >= v) { //t[x].val >= v，此时小于v的数只可能在左子树中
		if (t[x].ls == 0) //没有左子树，直接返回ans
			return ans;
		else //在左子树中继续查找
			return querylst(t[x].ls, v, ans);
	} else { //t[x].val < v，此时找到了比v小的数
		ans = max(t[x].val, ans); //更新ans的值
		if (t[x].rs == 0) //没有右子树，直接返回ans
			return ans;
		else { //在右子树中继续查找，试图找到更大的ans
			return querylst(t[x].rs, v, ans);
		}
	}
}

int querynxt(int x, int v, int ans) { //查找某个数的后续
	//同上，注释省略
	if (x == 0)
		return ans;
	if (t[x].val <= v) {
		if (t[x].rs == 0)
			return ans;
		else
			return querynxt(t[x].rs, v, ans);
	} else {
		ans = min(t[x].val, ans);
		if (t[x].ls == 0)
			return ans;
		else {
			return querynxt(t[x].ls, v, ans);
		}
	}
}

int queryrk(int x, int v) { //查找某个数对应的排名（实际上返回的结果是(排名 - 1)）
	//在向下递归时返回的都是局部排名，只有在最顶层返回的才是真正的全局排名
	if (x == 0)
		return 0;
	if (t[x].val == v) //t[x].val == v，此时左子树的siz对应的就是局部排名
		return t[t[x].ls].siz;
	else if (t[x].val > v) //t[x].val > v，在左子树中继续查找
		return queryrk(t[x].ls, v);
	else //t[x].val < v，此时的局部排名是(左子树的siz + 当前元素出现次数 + 右子树查找到的局部排名)
		return t[t[x].ls].siz + t[x].cnt + queryrk(t[x].rs, v);
}

int querykth(int x, int rk) { //查找某个排名对应的数
	//在向下递归时传入的rk都是局部排名，只有在最顶层的rk才是全局排名
	if (x == 0)
		return inf;
	if (t[t[x].ls].siz >= rk) //t[t[x].ls].siz >= rk，说明左子树过大，继续往左子树查找
		return querykth(t[x].ls, rk);
	else if (t[t[x].ls].siz + t[x].cnt >= rk) //t[t[x].ls].siz + t[x].cnt >= rk，说明此时的数恰好是局部排名中的第rk个
		return t[x].val;
	else //t[t[x].ls].siz + t[x].cnt < rk，说明左子树和该元素都不够大，需要继续往右子树查找
		//并且新的局部排名需要减去左子树的siz和当前元素个数
		return querykth(t[x].rs, rk - t[t[x].ls].siz - t[x].cnt);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	srand(time(0)); // 初始化随机数种子
	int q, op, x; // q 为操作次数
	cin >> q;
	while (q--) {
		cin >> op;
		if (op >= 1 && op <= 6 || op == 9)
			cin >> x;
		if (op == 1) { // 插入
			add(root, x);
		} else if (op == 2) { // 删除
			remove(root, x);
		} else if (op == 3) { // 查找前驱
			cout << querylst(root, x, -inf) << endl;
		} else if (op == 4) { // 查找后继
			cout << querynxt(root, x, inf) << endl;
		} else if (op == 5) { // 查找排名
			cout << queryrk(root, x) + 1 << endl;
		} else if (op == 6) { // 查找第k小
			cout << querykth(root, x) << endl;
		} else if (op == 7) { // 查询最小值
			cout << querymin(root) << endl;
		} else if (op == 8) { // 查询最大值
			cout << querymax(root) << endl;
		} else if (op == 9) { // 查询是否存在
			cin >> x; // 这个操作需要额外读入 x
			if (search(root, x) == 1)
				cout << "Yes" << endl;
			else
				cout << "No" << endl;
		} else if (op == 10) { // 中序遍历
			travel(root);
			cout << endl;
		}
	}
	return 0;
}