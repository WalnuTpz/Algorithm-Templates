#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
const int maxn = 3000010;

int n, q, idx, ans, trie[maxn][65], cnt[maxn], isend[maxn];
string s;

int ctoi(char c) {
	if (c >= 'a' && c <= 'z')
		return c - 'a';
	else if (c >= 'A' && c <= 'Z')
		return c - 'A' + 26;
	else if (c >= '0' && c <= '9')
		return c - '0' + 52;
}

void insert(string s) { //²åÈë×Ö·û´®
	int u = 0, l = s.size();
	for (int i = 0; i < l; i++) {
		int x = ctoi(s[i]);
		if (trie[u][x] == 0)
			trie[u][x] = ++idx;
		cnt[trie[u][x]]++;
		u = trie[u][x];
	}
	isend[u] = 1;
}

void delete (string s) { //É¾³ý×Ö·û´®
	int u = 0, l = s.size();
	for (int i = 0; i < l; i++) {
		int x = ctoi(s[i]);
		cnt[trie[u][x]]--;
		u = trie[u][x];
	}
	isend[u] = 0;
}

int find(string s) { //²éÕÒÒ»¸ö×Ö·û´®ÊÇ·ñÔÚ×ÖµäÊ÷ÖÐ
	int u = 0, l = s.size();
	for (int i = 0; i < l; i++) {
		int x = ctoi(s[i]);
		if (trie[u][x] == 0)
			return 0;
		u = trie[u][x];
	}
	return isend[u];
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		insert(s);
	}
	for (int i = 1; i <= q; i++) {
		cin >> s;
		cout << find(s) << endl;
	}
	return 0;
}
