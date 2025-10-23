#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
const int maxn = 100010, inf = 2147483647;

int q, num, op, x, root;

struct node {
	int val, ls, rs, cnt, siz;
	//值，左孩子下标，右孩子下标，出现次数，子树大小（包含该节点大小）
} t[maxn];

void add(int x, int v) { //插入某一个数
	t[x].siz++;
	if (v == t[x].val) { //已经有这个数，只需把次数加一
		t[x].cnt++;
		return;
	} else if (v < t[x].val) { //v < t[x].val，说明v在x的左子树里
		if (t[x].ls != 0) //有左子树，则继续递归
			add(t[x].ls, v);
		else { //没有左子树，说明v是x的左孩子，添加节点
			num++;
			t[num].val = v;
			t[num].siz = t[num].cnt = 1;
			t[x].ls = num;
		}
	} else { //v > t[x].val，说明v在x的右子树里
		if (t[x].rs != 0) //有右子树，则继续递归
			add(t[x].rs, v);
		else { //没有右子树，说明v是x的右孩子，添加节点
			num++;
			t[num].val = v;
			t[num].siz = t[num].cnt = 1;
			t[x].rs = num;
		}
	}
}

int remove(int x, int v) { //删除某一个数（只将它的出现次数减小1），并返回删除后的根
	if (x == 0)
		return 0;
	if (v < t[x].val) { //v < t[x].val，说明v在x的左子树里，递归删除
		t[x].ls = remove(t[x].ls, v);
	} else if (v > t[x].val) { //v > t[x].val，说明v在x的右子树里，递归删除
		t[x].rs = remove(t[x].rs, v);
	} else { //已经找到v，进行删除操作
		t[x].cnt--; //出现次数减一
		if (t[x].cnt == 0) { //如果删除后出现次数为0，则需要把该节点删去
			if (t[x].ls == 0 && t[x].rs == 0) //没有左右孩子，返回0作为新的根
				return 0;
			else if (t[x].ls == 0) //没有左孩子，返回右孩子作为根
				return t[x].rs;
			else if (t[x].rs == 0) //没有右孩子，返回左孩子作为根
				return t[x].ls;
			else { //左右孩子都存在，此时将该节点替换为右子树中的最小节点
				int cur = t[x].rs;
				while (t[cur].ls != 0) //查找右子树中的最小节点
					cur = t[cur].ls;
				t[x].val = t[cur].val;
				t[x].cnt = t[cur].cnt;
				t[cur].cnt = 1; //将个数设置为1，让下一步的删除可以将节点直接删除
				t[x].rs = remove(t[x].rs, t[cur].val); //删除右子树中的最小节点
			}
		}
	}
	t[x].siz = t[x].cnt + t[t[x].ls].siz + t[t[x].rs].siz; //更新该节点的siz
	return x;
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
	if (x == 0)
		return 0;
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
	cin >> q;
	while (q--) {
		cin >> op >> x;
		if (op == 1)
			cout << queryrk(1, x) + 1 << endl;
		else if (op == 2)
			cout << querykth(1, x) << endl;
		else if (op == 3)
			cout << querylst(1, x, -inf) << endl;
		else if (op == 4)
			cout << querynxt(1, x, inf) << endl;
		else if (op == 5) {
			if (num == 0) {
				num++;
				t[num].val = x;
				t[num].siz = t[num].cnt = 1;
			} else
				add(1, x);
		} else if (op == 6)
			remove(1, x);
		else if (op == 7)
			cout << querymin(1) << endl;
		else if (op == 8)
			cout << querymax(1) << endl;
		else if (op == 9) {
			if (search(1, x) == 1)
				cout << "Yes" << endl;
			else
				cout << "No" << endl;
		} else {
			travel(1);
			cout << endl;
		}
	}
	return 0;
}
