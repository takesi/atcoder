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
  UnionFind(int N) { parent = vector<int>(N, -1); }
  // Aがどのグループに属しているかを調べる
  int root(int A) {
    if (parent[A] < 0) return A;
    return (parent[A] = root(parent[A]));
  }
  // 自分のいるグループの頂点数を調べる
  int size(int A) { return -parent[root(A)]; }
  // AとBをくっつける
  int connect(int A, int B) {
    // AとBを直接つなぐのではなくroot(A)とroot(B)をくっつける
    A = root(A);
    B = root(B);
    if (A == B) return false; // すでにくっついている
    // 大きい方(A)を小さい方(B)にくっつけたいので大小が逆だったらひっくり返す
    if (size(A) < size(B)) swap(A, B);
    parent[A] += parent[B]; // Aのサイズを更新する
    parent[B] = A;          // Bの親をAに変更する
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