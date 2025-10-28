#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 100010;

ll n, q, mod, op, x, y, k, a[maxn], t[maxn * 4], add[maxn * 4], mul[maxn * 4];

void push_up(ll p) { //向上更新
	t[p] = t[p * 2] + t[p * 2 + 1]; //子节点的值合并为父节点的值
}

void push_down(ll p, ll l, ll r) { //向下更新，重点是对于懒标记add,mul的传递
	ll mid = (l + r) / 2;
	add[p * 2] = (add[p * 2] * mul[p]) % mod;
	mul[p * 2] = (mul[p * 2] * mul[p]) % mod;
	t[p * 2] = (t[p * 2] * mul[p]) % mod; //左区间为[l, mid]
	add[p * 2 + 1] = (add[p * 2 + 1] * mul[p]) % mod;
	mul[p * 2 + 1] = (mul[p * 2 + 1] * mul[p]) % mod;
	t[p * 2 + 1] = (t[p * 2 + 1] * mul[p]) % mod; //右区间为[mid + 1, r]
	mul[p] = 1;
	add[p * 2] += add[p];
	t[p * 2] = (t[p * 2] + add[p] * (mid - l + 1)) % mod;
	add[p * 2 + 1] += add[p];
	t[p * 2 + 1] = (t[p * 2 + 1] + add[p] * (r - mid)) % mod;
	add[p] = 0;
}

void build(ll p, ll l, ll r) { //建树
	add[p] = 0;
	mul[p] = 1;
	if (l == r) {
		t[p] = a[l];
		return;
	}
	ll mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	push_up(p); //此时左右子节点已经更新完成，向上传递并更新当前节点
}

void update_add(ll nl, ll nr, ll l, ll r, ll p, ll k) { //更新加法
	if (nl <= l && r <= nr) { //当前节点的范围在目标范围内，直接更新节点
		t[p] = (t[p] + k * (r - l + 1)) % mod;
		add[p] = (add[p] + k) % mod;
		return;
	}
	push_down(p, l, r); //否则先向下更新，然后根据mid的值决定是否更新左右子树
	ll mid = (l + r) / 2;
	if (nl <= mid)
		update_add(nl, nr, l, mid, p * 2, k);
	if (mid + 1 <= nr)
		update_add(nl, nr, mid + 1, r, p * 2 + 1, k);
	push_up(p); //此时左右子节点已经更新完成，向上传递并更新当前节点
}

void update_mul(ll nl, ll nr, ll l, ll r, ll p, ll k) { //更新乘法，同上
	if (nl <= l && r <= nr) {
		t[p] = (t[p] * k) % mod;
		add[p] = (add[p] * k) % mod;
		mul[p] = (mul[p] * k) % mod;
		return;
	}
	push_down(p, l, r);
	ll mid = (l + r) / 2;
	if (nl <= mid)
		update_mul(nl, nr, l, mid, p * 2, k);
	if (mid + 1 <= nr)
		update_mul(nl, nr, mid + 1, r, p * 2 + 1, k);
	push_up(p);
}

ll query(ll nl, ll nr, ll l, ll r, ll p) { //查询
	ll ans = 0;
	if (nl <= l && r <= nr) //当前范围在目标范围内，说明t[p]是所需答案的一部分，直接返回t[p]
		return t[p];
	ll mid = (l + r) / 2;
	push_down(p, l, r); //否则先向下更新，然后根据mid的值决定是否累加左右子树的值
	if (nl <= mid)
		ans += query(nl, nr, l, mid, p * 2);
	if (mid + 1 <= nr)
		ans += query(nl, nr, mid + 1, r, p * 2 + 1);
	return ans % mod;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q >> mod;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n);
	for (int i = 1; i <= q; i++) {
		cin >> op;
		if (op == 1) { //乘法
			cin >> x >> y >> k;
			update_mul(x, y, 1, n, 1, k);
		}
		if (op == 2) { //加法
			cin >> x >> y >> k;
			update_add(x, y, 1, n, 1, k);
		}
		if (op == 3) { //查询
			cin >> x >> y;
			ll ans = query(x, y, 1, n, 1);
			cout << ans << endl;
		}
	}
	return 0;
}

/*
本题要用到add,sum两个标记，初始值add[i] = 0, mul[i] = 1。考虑push_down中父节点的add,mul对子节的add,mul,sum（也就是t数组）点有何影响：
考虑此时子节点的实际值为(sum * mul + add * (r - l + 1)) * Mul + Add  * (r - l + 1) = sum * (mul * Mul) + (add * Mul + Add) * (r - l + 1)，
也就是父节点的Mul会让子节点的add *= Mul, mul *= Mul, sum *= Mul；父节点的Add会让子节点的add += Add, sum += add * (r - l + 1), mul无影响。
然后考虑push_down中add, mul标记下传的顺序，由于新的add为(add * Mul + Add)，所以要先下传mul再下传add。update里面也是同理，
update_add只会改变add, sum，update_mul会改变add, mul, sum。
*/
