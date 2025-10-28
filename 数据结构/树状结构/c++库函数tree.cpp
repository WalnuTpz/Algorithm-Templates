#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

typedef long long LL;

tree<LL, null_type, less<LL>, rb_tree_tag, tree_order_statistics_node_update> treap;

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int opt;
		LL x;
		cin >> opt >> x;
		if (opt == 1) {
			treap.insert( (x << 20) + i );
		} else if (opt == 2) {
			treap.erase(treap.lower_bound(x << 20));
		} else if (opt == 3) {
			cout << ( treap.order_of_key(x << 20) + 1 ) << "\n";
		} else if (opt == 4) {
			cout << ( (*treap.find_by_order(x - 1)) >> 20 ) << "\n";
		} else if (opt == 5) {
			auto t = treap.lower_bound(x << 20);
			t--;
			cout << ( (*t) >> 20 ) << "\n";
		} else if (opt == 6) {
			cout << ( (*treap.upper_bound( (x << 20) + n )) >> 20 ) << "\n";
		}
	}
	return 0;
}