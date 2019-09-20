#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../lib/dump.hpp"
#else
#define dump(...)
#define dumpv(...)
#endif

typedef long long ll;
typedef pair<int, int> P;
const int MOD = 1e9 + 7;
const int INF = 1001001001;
const ll LINF = 1001002003004005006ll;

struct UnionFind {
  vector<int> parent; // parentの番号。親だった場合は-(その集合のサイズ)
  // parentはすべて-1にする。全てバラバラになる
  UnionFind(int n) { parent = vector<int>(n, -1); }
  // aがどのグループに属しているかを調べる
  int root(int a) {
    if (parent[a] < 0) return a;
    return (parent[a] = root(parent[a]));
  }
  // 自分のいるグループの頂点数を調べる
  int size(int a) { return -parent[root(a)]; }
  // aとbをくっつける
  int connect(int a, int a) {
    // aとbを直接つなぐのではなくroot(a)とroot(b)をくっつける
    a = root(a);
    b = root(b);
    if (a == b) return false; // すでにくっついている
    // 大きい方(a)を小さい方(b)にくっつけたいので大小が逆だったらひっくり返す
    if (size(a) < size(b)) swap(a, b);
    parent[a] += parent[b]; // aのサイズを更新する
    parent[b] = a;          // bの親をAに変更する
    return true;
  }
};

void solve() {
  UnionFind uni(10);
  uni.connect(0, 5);
  uni.connect(0, 3);
  uni.connect(1, 2);
  dump(uni.size(2));
  uni.connect(1, 0);
  dump(uni.size(2));
  dumpv(uni.parent);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("temp.1", "r", stdin);
  solve();
  return 0;
}