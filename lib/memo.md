# ライブラリ (c++)

## 計算量や定数など

- 桁数とビット数の関係

  | ビット数         | 2進数    | 10進数                  | 実際の最大値              |
  | ---------------- | -------- | ----------------------- | ------------------------- |
  | 20               | $2^{20}$ | $\sim 1 \times 10^6$    | 1,048,576                 |
  | 30               | $2^{30}$ | $\sim 1 \times 10^9$    | 1,073,741,824             |
  | 31 (`int`)       | $2^{31}$ | $\sim 2 \times 10^9$    | 2,147,483,648             |
  | 60               | $2^{60}$ | $\sim 1 \times 10^{18}$ | 1,152,921,504,606,846,976 |
  | 63 (`long long`) | $2^{63}$ | $\sim 9 \times 10^{18}$ | 9,223,372,036,854,775,808 |

  

- 計算量 (2秒制限の場合) の目安

  | 計算量    | 時間             |      |
  | --------- | ---------------- | ---- |
  | $O(10^7)$ | 余裕で間に合う   |      |
  | $O(10^8)$ | おそらく間に合う |      |
  | $O(10^9)$ | かなり厳しい     |      |

  | Nのサイズ      | 可能な計算量 | アルゴリズム例 |
  | -------------- | ------------ | -------------- |
  | $10^7\sim10^8$ | $O(N)$       |                |
  | $10^5\sim10^6$ | $O(NlogN)$   |                |
  | $10^4$         | $O(N^2)$     |                |
  | $300$          | $O(N^3)$     |                |
  | $100$          | $O(N^4)$     |                |
  | $20$           | $O(2^N)$     |                |

  [計算量]: https://qiita.com/drken/items/872ebc3a2b5caaa4a0d0


- 定数

  ```
  M_PI // 3.14...の定数
  ```

- 注意点

  - std::listのsizeがO(N)になっているバグがある。
  - 「より真に小さい」は「より小さい」のこと。

## データ操作系

- 重複の削除

  ```c++
  vector<int> v;
  // input data into v
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  ```

  

- lower_boundとupper_boundの使い方

  ```c++
  multiset<int> st = { 1, 2, 2, 3, 3, 5, 5, 7 }; // setも同様
  // vectorの場合はソートしておき、lower_bound(v.begin(), v.end(), x)と呼ぶ
  { // 3より小さい値
    auto it = st.lower_bound(3);
    if (it == st.begin()) return; // 存在しない
    it--;
    dump(*it);
  }
  { // 3以下の値
    auto it = st.upper_bound(3);
    if (it == st.begin()) return; // 存在しない
    it--;
    dump(*it);
  }
  { // 4より大きい値
    auto it = st.upper_bound(4);
    if (it == st.end()) return; // 存在しない
    dump(*it);
  }
  { // 4以上の値
    auto it = st.lower_bound(4);
    if (it == st.end()) return; // 存在しない
    dump(*it);
  }
  { // 3以上6以下を削除
    auto l = st.lower_bound(3);
    auto r = st.upper_bound(6);
    st.erase(l, r);
    dump(st);
  }
  ```

  

## アルゴリズム系

- 二分検索

  ```c++
int left = -1; // a[0]がダメなこともあるので初期値は-1
  int right = (int)a.size(); // a[a.size()-1]がダメなこともあるので初期値はa.size()
  while (right - left > 1) {
      int mid = left + (right - left) / 2;
      if (isOk(mid)) right = mid; // 例えば(key<=a[mid])など
      else left = mid;
  }
  // leftは条件を満たさない最大の値、rightは条件を満たす最小の値になっている
  ```
  
  
  
- 尺取法

  データ列の区間最小値や最大値を求める時に使う。O(N)で可能。

  ```c++
  int left = 0;
  int right = 0;
  int val = 0; // 区間[left, right)の合計値
  int ans = -INF;
  for (int i = 0; i < data.size(); i++) {
    // 次のleft, rightを決める
    int nleft = i;
    int nright = min(i + K, data.size()); // K個の分の区間
    while (left < nleft) {
      val -= data[left];
      left++;
    }
    while (right < nright) {
      val += data[right];
      right++;
    }
    ans = max(val, ans);
  }
  ```

  

- スライド最小値

  工事中

  

- 座標圧縮

  mapが自動的に昇順ソートされることを使って圧縮するコード。同じ値があっても大丈夫。このコードでは元の配列を書き換える。

  ```c++
  map<int, int> mp;
  for (int i = 0; i < N; i++) {
    mp[data[i]] = 0;
  }
  int j = 0;
  for (auto& x : mp)
    x.second = j++;
  for (int i = 0; i < N; i++) {
    data[i] = mp[data[i]];
  }
  ```

  

- BIT (Fenwick Tree)

  セグ木の簡易版で合計値だけを簡単に計算する時に使う。2次元配列のインプリもある。計算量も同じ$O(logN)$。

  [bit]: ../lib/bit.cpp

  

- セグ木

  区間$[a b)$の最小、最大、合計などを$O(logN)$で計算する時に使う。更新(update)も$O(logN)$かかる。初期配列を用意した場合は$O(N)$で初期化できる。

  [SegTree]: ../lib/segtree.cpp

  

- ローリングハッシュ

  文字列の比較を$O(1)$で行うことができる。ハッシュをconcatして新たなハッシュを作成できるので1文字変更して比較するなどがとても高速。

  [RollingHash]: ../lib/rolling-hash.cpp

  

- 順列と組み合わせ

  フェルマーの小定理を使ったmod版の順列と組み合わせはこっち。mintとmsetを組み合わせて使う。

  [mint]: ../lib/mint.cpp

  順列と組み合わせを配列に全列挙してくれるnext_permutation2とnext_combinationの入ったライブラリはこっち。next_permulationにはK個を指定できなくて配列全部が対象になってしまうのでnext_permutation2を作った。

  [perm-comb]: ../lib/perm-comb.cpp

  組み合わせだけサクッと欲しい場合のメモ化再帰コード。[libalgo][libalgo]から。

  ```c++
  const int MAX_N = 10000;  // 400MB (1024=4MB)
  ll nCr(int n, int r) {
      static bool done[MAX_N + 1][MAX_N / 2 + 2];
      static ll dp[MAX_N + 1][MAX_N / 2 + 2];
      if (n < 0 || r < 0 || n < r) return 0;
      if (r == 0) return 1;
      if (r > n - r) r = n - r;
      ll &res = dp[n][r];
      if (done[n][r]) return res;
      done[n][r] = true;
      return res = (nCr(n - 1, r - 1) + nCr(n - 1, r)) % MOD;
  }
  ```

  

- 素数の列挙

  これが良いコードなのかわからない。

  ```c++
  // mx以下の素数をprimeに入れる
  vector<int> is_prime(mx + 1, 1);
  vector<int> prime;
  for (int i = 2; i <= mx; i++) {
    if (is_prime[i]) {
      for (int j = 2 * i; j <= mx; j += i)
        is_prime[j] = 0; // 素数の倍数を排除
      prime.push_back(i);
    }
  }
  ```
  

  
- ダブリング

  工事中

## グラフ系

- 用語

  - DAG は Directed Acyclic Graph の略で、閉路のない有向グラフのこと

  

- 到達可能かはdfsをして調べる。ゴールは逆辺をdfsすればいい。

- 最長経路問題は辺のコストを逆転して最短経路問題にする。

  

- Union Find

  高速に親子関係をグループ化できる。グループの要素数も高速に取得可能。

  [UnionFind]: ../lib/union-find.cpp

  

- ダイクストラ法
  負辺のない単一始点全点間最短距離を求めるアルゴリズム。proirity_queueで実装する。計算量はMを辺の数、Nを頂点数とすると$O(MlogN)$

  [Dijkstra]: ../lib/dijkstra.cpp

  

- ワーシャルフロイド法

  グラフの全ての頂点の間の最短路を見つけるアルゴリズム。実装には全頂点間の重みを持つ。計算量は頂点数をNとすると$O(N^3)$

  ```c++
  vector<vector<int>> dist(N, vector<int>(N, INF)); // dist[from][to]
  rep(i, N) dist[i][i] = 0; // 自分自身への距離は0
  // ここで重みを入力する（無向辺は両方向に）
  rep(k, N) rep(i, N) rep(j, N) {
    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    // 経路復元をしたい場合は経由頂点を更新時に覚えて後で再帰的にたどる
  }
  ```

  [Warshall Floyd]: ../lib/warshall-floyd.cpp

   

- ベルマンフォード法

  グラフの二点間の最短距離を求めるアルゴリズム。Dijkstra法と比べて辺の重みが負でも動くが、重みに負の数がないならDijkstra法を使った方が高速。実装には辺のリストを持つ。負閉路の検出が可能。計算量はMを辺の数、Nを頂点数とすると$O(MN)$

  ```c++
  vector<int> dist(N, INF); // 距離を初期化 (N頂点数)
  dist[0] = 0; // 開始点は0にする
  int updated = 1;
  int step = 0;
  while (updated) {
    updated = 0;
    rep(i, eg.size()) { // 辺を全てスキャン
      int u, v, c;
      tie(u, v, c) = eg[i];
      if (dist[a] + c < dist[b]) {
        updated = 1;
        dist[b] = dist[a] + c;
      }
    }
    step++;
    if (N < step) break; // 負閉路が存在
  }
  ```

  

- トポロジカルソートと閉路検出

  有向グラフをトポロジカルソートすると各有向辺が順方向にならぶ。これができない場合は閉路があるので検出可能。

  ```c++
  vector<int> used(V); // 1: visited, 2: completed
  vector<int> res;
  int loop = false; // 閉路のフラグ
  function<void(int)> dfs = [&](int u) {
    if (used[u]) {
      if (used[u] == 1) loop = true;
      return;
    }
    used[u] = 1;
    for (auto& v : to[u]) dfs(v);
    used[u] = 2;
    res.push_back(u); // 帰りがけ順で追加
  };
  rep(i, V) {
    dfs(i);
    if (loop) break; // 閉路が存在
  }
  reverse(res.begin(), res.end());
  ```
  

  
- 最大流

  Dinic法のライブラリはここ。

  [dinic]: ../lib/dinic.cpp

  

- LCA

  

## DP系

- ナップサック

  

- 最長共通部分列(LCS)

  文字列sとtが与えられて共通部分文字列の最大値を求める。配るdpの実装。

  ```c++
  // dp[s.size() + 2][t.size() + 2]のテーブルが必要
  rep(i, s.size() + 1) rep(j, t.size() + 1) {
    dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
    dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
    if (i < s.size() && j < t.size() && s[i] == t[j]) {
      dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 1);
    }
  }
  cout << dp[s.size()][t.size()] << endl;
  ```

  

- メモ化

- 桁DB

  

## サイトリンク集

[yukicoder]: https://yukicoder.me/wiki/algorithm_summary
[c++ snippet]: https://satanic0258.github.io/snippets/index.html
[東工大trap]: https://trap.jp/post/152/
[Spaghetti Source]: http://www.prefield.com/algorithm/
[libalgo]: https://tubo28.me/compprog/algorithm/

