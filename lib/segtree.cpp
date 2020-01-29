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

template<typename T>
struct SegTree {
  int n;
  T init; // 単位元(初期値)
  vector<T> node;
  function<T(T&, T&)> calc; // 子ノード2つから親ノードのデータにする処理
  SegTree(int sz, T init, function<T(T&, T&)> calc) : n(1), init(init), calc(calc) {
    while (n < sz) n *= 2; // 最下段のノード数は2のべき乗(n)
    node.resize(2 * n - 1, init); // セグメント木全体で必要なノード数は2n-1個である
  }
  SegTree(vector<T>& v, T init, function<T(T&, T&)> calc) : SegTree(v.size(), init, calc) {
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

// 遅延評価用のSegTree
enum queryType { SUM, MAX, MIN };
enum applyType { UPDATE, ADD };
template<typename T>
struct LazySegTree {
  queryType qtype;
  applyType atype;
  int n;
  T init; // 単位元(初期値)
  vector<T> node;
  vector<T> lazy;
  vector<int> lazyFlag;
  function<T(T&, T&)> calc; // 子ノード2つから親ノードのデータにする処理
  // 初期値と処理関数の設定
  void setQuery() {
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
  }
  LazySegTree(int sz, queryType qtype, applyType atype) : n(1), qtype(qtype), atype(atype) {
    setQuery();
    while (n < sz) n *= 2; // 最下段のノード数は2のべき乗(n)
    node.resize(2 * n - 1, init); // セグメント木全体で必要なノード数は2n-1個である
    lazy.resize(2 * n - 1, 0);
    lazyFlag.resize(2 * n - 1, false);
  }
  LazySegTree(vector<T>& v, queryType qtype, applyType atype) : LazySegTree(v.size(), qtype, atype) {
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
  // k 番目のノードについて遅延評価を行う
  void eval(int k, int l, int r) {
    if (qtype == SUM) {
      if (lazy[k] != 0) {
        // 遅延配列が空でない場合、自ノード及び子ノードへの値の伝播が起こる
        if (atype == UPDATE)
          node[k] = lazy[k];
        else
          node[k] += lazy[k];
        // 最下段かどうかのチェック
        if (r - l > 1) {
          // 子ノードは親ノードの 1/2 の範囲であるため、伝播させるときは半分にする
          lazy[2 * k + 1] += lazy[k] / 2;
          lazy[2 * k + 2] += lazy[k] / 2;
        }
        lazy[k] = 0; // 伝播が終わったので、自ノードの遅延配列を空にする
      }
    } else {
      if (lazyFlag[k]) {
        if (atype == UPDATE)
          node[k] = lazy[k];
        else
          node[k] += lazy[k];
        // 最下段かどうかのチェック
        if (r - l > 1) {
          lazy[2 * k + 1] = lazy[k], lazyFlag[2 * k + 1] = true;
          lazy[2 * k + 2] = lazy[k], lazyFlag[2 * k + 2] = true;
        }
        lazyFlag[k] = false; // 伝播が終わったので、自ノードの遅延配列を終了する
      }
    }
  }
  // 要求区間 [a, b) 中の要素に一様に遅延処理
  void apply(int a, int b, T v, int k = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;
    eval(k, l, r); // k 番目のノードに対して遅延評価を行う
    if (b <= l || r <= a) return; // 範囲外なら何もしない
    if (a <= l && r <= b) {
      // 完全に被覆しているならば、遅延配列に値を入れた後に評価
      if (qtype == SUM) {
        lazy[k] += (r - l) * v;
      } else {
        lazy[k] = v, lazyFlag[k] = true;
      }
      eval(k, l, r);
    }
    else {
      // そうでないならば、子ノードの値を再帰的に計算して、
      // 計算済みの値をもらってくる
      apply(a, b, v, 2 * k + 1, l, (l + r) / 2);
      apply(a, b, v, 2 * k + 2, (l + r) / 2, r);
      node[k] = calc(node[2 * k + 1], node[2 * k + 2]);
    }
  }
  // 要求区間 [a, b) 中の要素のquery
  // k := 自分がいるノードのインデックス、対象区間は [l, r) にあたる
  T query(int a, int b, int k = 0, int l = 0, int r = -1) {
    // 最初に呼び出されたときの対象区間は [0, n)
    if (r < 0) r = n;
    // 要求区間と対象区間が交わらない -> 適当に返す
    if (r <= a || b <= l) return init;
    eval(k, l, r); // 遅延評価
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

void solve() {
  int N = 8;
  // 配列の初期値を作成
  vector<int> data(N);
  for (int i = 0; i < N; i++) {
    data[i] = rand() % 8;
  }
  dump(data);

  // 区間の合計を取り出すSegTree
  SegTree<int> st_sum(data, 0, [](int& v1, int& v2) { return v1 + v2; });
  dump(st_sum.node);
  int v = st_sum.query(1, 5);
  dump("sum", v);

  // 区間の最小を取り出すSegTree
  SegTree<int> st_min(data, INF, [](int& v1, int& v2) { return min(v1, v2); });
  dump(st_min.node);
  v = st_min.query(1, 5);
  dump("min", v);

  // 区間の最大を取り出すSegTree (初期配列なし)
  SegTree<int> st_max(N, -INF, [](int& v1, int& v2) { return max(v1, v2); });
  for (int i = 0; i < N; i++) {
    st_max.update(i, rand() % 8); // 値を更新
  }
  dump(st_max.node);
  v = st_max.query(1, 5);
  dump("max", v);

  // 遅延評価用のLazySegTree
  LazySegTree<int> lst_sum(data, SUM, ADD);
  lst_sum.apply(0, 3, 1);
  rep(i, N) cout << lst_sum.query(i, i + 1) << " ";
  cout << endl;

  LazySegTree<int> lst_max(N, MAX, ADD);
  // rep(i, N) lst_max.update(i, rand() % 8); // 値を更新
  rep(i, N) lst_max.update(i, data[i]); // 値を更新
  rep(i, N) cout << lst_max.query(i, i + 1) << " ";
  cout << endl;
  cout << lst_max.query(1, 6) << endl;
  lst_max.apply(2, 4, 6);
  rep(i, N) cout << lst_max.query(i, i + 1) << " ";
  cout << endl;
  cout << lst_max.query(1, 6) << endl;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("temp.1", "r", stdin);
  solve();
  return 0;
}