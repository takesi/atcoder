#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../lib/dump.hpp"
#else
#define dump(...)
#define dumpv(...)
#endif

#define rep(i, n) for (int i = 0; i < (n); i++)
typedef long long ll;
typedef pair<int, int> P;
const int MOD = 1e9 + 7;
const int INF = 1001001001;
const ll LINF = 1001002003004005006ll;

// %start
enum queryType { SUM, MAX, MIN };
template<typename T>
struct SegTree {
  int n;
  T init; // 単位元(初期値)
  vector<T> node;
  function<T(T&, T&)> calc; // 子ノード2つから親ノードのデータにする処理
  SegTree(int sz, queryType qtype) : n(1) {
    // 初期値と処理関数の設定
    switch (qtype) {
      case SUM:
        init = 0;
        calc = [](T& v1, T& v2) { return v1 + v2; };
        break;
      case MAX:
        init = std::numeric_limits<T>::lowest();
        calc = [](T& v1, T& v2) { return (v1 > v2) ? v1 : v2; };
        break;
      case MIN:
        init = std::numeric_limits<T>::max();
        calc = [](T& v1, T& v2) { return (v1 < v2) ? v1 : v2; };
        break;
    }
    while (n < sz) n *= 2; // 最下段のノード数は2のべき乗(n)
    node.resize(2 * n - 1, init); // セグメント木全体で必要なノード数は2n-1個である
  }
  SegTree(vector<T>& v, queryType qtype) : SegTree(v.size(), qtype) {
    // 最下段に値を入れたあとに、下の段から順番に値を入れる
    // 値を入れるには、自分の子の2値を参照すれば良い
    // ノードiの親は(i-1)/2、子は(2i+1,2i+2)で見つける
    for (int i = 0; i < v.size(); i++) node[i + n - 1] = v[i];
    for (int i = n - 2; i >= 0; i--) node[i] = calc(node[2 * i + 1], node[2 * i + 2]);
  }
  void update(int i, T v) {
    i += (n - 1); // 最下段のノードにアクセスする
    // 最下段のノードを更新したら、あとは親に上って更新していく
    node[i] = v;
    while (i > 0) {
      i = (i - 1) / 2; // 1つ親にする
      node[i] = calc(node[2 * i + 1], node[2 * i + 2]);
    }
  }
  // 要求区間 [a, b) 中の要素の最小値を答える
  // k := 自分がいるノードのインデックス、対象区間は [l, r) にあたる
  T query(int a, int b, int k = 0, int l = 0, int r = -1) {
    // 最初に呼び出されたときの対象区間は [0, n)
    if (r < 0) r = n;
    // 要求区間と対象区間が交わらない -> 適当に返す
    if (r <= a || b <= l) return init;
    // 要求区間が対象区間を完全に被覆 -> 対象区間を答えの計算に使う
    if (a <= l && r <= b) return node[k];
    // 要求区間が対象区間の一部を被覆 -> 子について探索を行う
    // 左側の子を vl ・ 右側の子を vr としている
    // 新しい対象区間は、現在の対象区間を半分に割ったもの
    T vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
    T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
    return calc(vl, vr);
  }
};
// %end

void solve() {
  int N = 8;
  // 配列の初期値を作成
  vector<int> data(N);
  for (int i = 0; i < N; i++) {
    data[i] = rand() % 8;
  }
  dump(data);

  // 区間の合計を取り出すSegTree
  SegTree<int> st_sum(data, SUM);
  dump(st_sum.node);
  int v = st_sum.query(1, 5);
  dump("sum", v);

  // 区間の最小を取り出すSegTree
  SegTree<int> st_min(data, MIN);
  dump(st_min.node);
  v = st_min.query(1, 5);
  dump("min", v);

  // 区間の最大を取り出すSegTree (初期配列なし)
  SegTree<int> st_max(N, MAX);
  for (int i = 0; i < N; i++) {
    st_max.update(i, data[i]); // 値を更新
  }
  dump(st_max.node);
  v = st_max.query(1, 5);
  dump("max", v);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("temp.1", "r", stdin);
  solve();
  return 0;
}