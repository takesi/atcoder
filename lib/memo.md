# ライブラリ (c++)

## 計算量や定数など

- 桁数とビット数の関係

  | ビット数         | 2進数    | 10進数                     | 実際の最大値              |
  | ---------------- | -------- | -------------------------- | ------------------------- |
  | 20               | $2^{20}$ | $\approx 1 \times 10^6$    | 1,048,576                 |
  | 30               | $2^{30}$ | $\approx 1 \times 10^9$    | 1,073,741,824             |
  | 31 (`int`)       | $2^{31}$ | $\approx 2 \times 10^9$    | 2,147,483,648             |
  | 40               | $2^{40}$ | $\approx 1 \times 10^{12}$ | 1,099,511,627,776         |
  | 60               | $2^{60}$ | $\approx 1 \times 10^{18}$ | 1,152,921,504,606,846,976 |
  | 63 (`long long`) | $2^{63}$ | $\approx 9 \times 10^{18}$ | 9,223,372,036,854,775,808 |

  

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

  一般的な書き方。配列の要素`[0:N)`から見つける場合にはそのまま使えるが、最大長を二分探索する場合は`left=0,right=max+1`で行うと最低でも`isOk(max)`が実行される。その場合は`while`ループを抜けた後の`right`は正しくない。必要な処理を`isOk()`の`if`分の中に書く。

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
  
  下記のような書き方もあるみたいなので参考として載せておく。
  
  ```c++
  int left = 0;
  int right = (int)a.size();
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (target == a[mid]) {
      // 必要な処理を書く
      break;
    } else if (target < a[mid]) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
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

  幅を求めたい場合は下記の方法。

  ```c++
  // 区間の左端leftでloop
  int right = 0; // 毎回rightを使い回すようにする
  ll sum = 0;    // sumも使い回す
  for (int left = 0; left < n; left++) {
    // sumにa[right]を加えても大丈夫ならrightを動かす
    while (right < n && (sum + a[right]) <= x) {
      sum += a[right];
      right++;
    }
    // breakした状態でrightは条件を満たす最大
    ans += (right - left);
    // leftをインクリメントする準備
    if (right == left)
      right++; // rightがleftに重なったらrightも動かす
    else
      sum -= a[left]; // leftのみがインクリメントされるのでsumからa[left]を引く
  }
  ```

  

- スライド最小値

  工事中

  

- 座標圧縮

  mapが自動的に昇順ソートされることを使って圧縮するコード。同じ値があっても大丈夫。このコードでは元の配列を書き換える。

  ```c++
  { // geometry compression
    map<int, int> mp;
    rep(i, n) mp[a[i]] = 0;
    int idx = 0;
    for (auto& m : mp) m.second = idx++;
    rep(i, n) b[i] = mp[a[i]];
  }
  ```
  
  
  
- BIT (Fenwick Tree)

  セグ木の簡易版で合計値だけを簡単に計算する時に使う。2次元配列のインプリもある。計算量も同じ$O(logN)$。

  [bit]: ../lib/bit.cpp

  

- セグ木

  区間$[a b)$の最小、最大、合計などを$O(logN)$で計算する時に使う。更新(update)も$O(logN)$かかる。初期配列を用意した場合は$O(N)$で初期化できる。

  [SegTree]: ../lib/segtree.cpp

  

- 順列と組み合わせ

  フェルマーの小定理の逆元を使ったmod版の順列`nPk()`と組み合わせ`nCk()`はこっち。mintとみ合わせて使う。

  [mint]: ../lib/mint.cpp

  順列と組み合わせを配列に全列挙してくれるnext_permutation2とnext_combinationの入ったライブラリはこっち。next_permulationにはK個を指定できなくて配列全部が対象になってしまうのでnext_permutation2を作った。

  [perm-comb]: ../lib/perm-comb.cpp

  組み合わせだけサクッと欲しい場合のメモ化再帰コード。[libalgo][libalgo]から。値が大きくなるととっても遅くなるので注意。

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
  

  
- 素因数分解

  素因数分解した$p_1^{e_1}p_2^{e_2}\cdots p_k^{e_k}$の約数の数は$(e_1 + 1)(e_2 + 1)\cdots (e_k + 1)$で計算できる。
  
  ```c++
  map<ll, int> prime_factor(ll n) {
    map<ll, int> ret;
    for (ll i = 2; i * i <= n; i++) {
      while (n % i == 0) {
        ret[i]++;
        n /= i;
      }
    }
    if (n != 1) ret[n] = 1;
    return ret;
  }
  ```
  
  [prime_factor]: https://ei1333.github.io/luzhiled/snippets/math/prime-factor.html
  
  
  
- ダブリング

  工事中
  
  
  
- ガウス消去法

  配列のすべてのサブセット間の最大xorを求める。

  ```c++
  // ガウス消去法 (xor)
  ll GaussElimination(vl& v) {
    int n = v.size();
    int idx = 0;
    for (int b = 60; 0 <= b; b--) {
      int x = idx;
      while (x < n && ((v[x] >> b) & 1) == 0) x++;
      if (x == n) continue; // もしbitが1の要素がなければスキップ
      swap(v[idx], v[x]);
      rep(i, n) if ((i != idx) && (((v[i] >> b) & 1) == 1)) v[i] ^= v[idx];
      idx++;
    }
    // 部分集合の最大xor値を返す
    ll mx = 0;
    rep(i, n) mx ^= v[i];
    return mx;
  }
  ```

  

## 文字列

- 文字列型

  ```c++
  string s;
  s.substr(pos, len); // posからlen分取り出す
  s.substr(pos); // posから最後まで取り出す
  s.c_str(); // char *で返す
  s = to_string(0.123); // stringに変換
  ```

  

- ローリングハッシュ

  文字列の比較を$O(1)$で行うことができる。ハッシュをconcatして新たなハッシュを作成できるので1文字変更して比較するなどがとても高速。

  [RollingHash]: ../lib/rolling-hash.cpp

  

- Z-Algorithm

  同じ文字列内での一致した長さを配列的に返す関数。

  ```c++
  vector<int> z_algorithm(const string &s) {
    vector<int> prefix(s.size());
    for (int i = 1, j = 0; i < s.size(); i++) {
      if (i + prefix[i - j] < j + prefix[j]) {
        prefix[i] = prefix[i - j];
      } else {
        int k = max(0, j + prefix[j] - i);
        while (i + k < s.size() && s[k] == s[i + k]) ++k;
        prefix[i] = k;
        j = i;
      }
    }
    prefix[0] = (int)s.size();
    return prefix;
  }
  ```

  [z-algorithm]: https://ei1333.github.io/luzhiled/snippets/string/z-algorithm.html

  

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
  // dp[s.size() + 1][t.size() + 1]のテーブルが必要
  rep(i, s.size() + 1) rep(j, t.size() + 1) {
    dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
    dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
    if (i < s.size() && j < t.size() && s[i] == t[j]) {
      dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 1);
    }
  }
  cout << dp[s.size()][t.size()] << endl;
  ```

  集めるdpの実装。こちらの方は`dp[i][j]`の値が`(i,j)`の位置から最大いくつ一致しているかが取れるので再利用しやすい。配るdpだと最後の答えだけしか正しくない。

  ```c++
  // dp[s.size() + 1][t.size() + 1]のテーブルが必要
  for (int i = s.size() - 1; 0 <= i; i--) {
    for (int j = t.size() - 1; 0 <= j; j--) {
      if (s[i] == t[j]) {
        dp[i][j] = max(dp[i][j], dp[i + 1][j + 1] + 1);
      }
    }
  }
  ```

  

- メモ化

  一度計算した値を記録しておいて再度計算しないようにする。再帰関数などで2度めは深くcallしなくても良いようにして計算量を減らす。

  

- 桁DB

  上の桁から見ていく。より小さいフラグ`less`を使って遷移を書く。数を数える場合は初期値を0にして最初の遷移の元を1にする。最大値の場合は初期値を-1にして最初の遷移の元を0にする（この場合-1からは遷移させないようにする）。3番目以降のdp変数は「ある数字が出たかどうか 0/1」や「ある数字が出た回数 0〜数字が出る個数のmax」などにすると良い。
  
  ```c++
  // 単に入力文字列s以下の個数を計算するだけのテンプレート
  int n = s.size();
  dp[0][0] = 1;
  rep(i, n) rep(less, 2) rep(d, 2) { // 10進数なら10にする
    int x = (int)(s[i] - '0');
    int nless = less;
    if (less == 0 && x < d) continue;
    if (less == 0 && x > d) nless = 1;
    dp[i + 1][nless] += dp[i][less];
  }
  ```
  
  
  
  

## サイトリンク集

[Luzhiled's memo]: https://ei1333.github.io/luzhiled/
[yukicoder]: https://yukicoder.me/wiki/algorithm_summary
[c++ snippet]: https://satanic0258.github.io/snippets/index.html
[東工大trap]: https://trap.jp/post/152/
[Spaghetti Source]: http://www.prefield.com/algorithm/
[libalgo]: https://tubo28.me/compprog/algorithm/

# ライブラリ (python3.4)

## テンプレート

- input, map

  ```python
  s = input() # abcde
  x = int(input()) # 3
  n, m = map(int, input().split()) # 10 20
  a = list(map(int, input().split())) # 1 2 3 4 5 ...
  b = [0] * 5 # [0, 0, 0, 0, 0]
  c = []
  for i in range(5):
    c.append(i)
  print(c) # [0, 1, 2, 3, 4]
  print(*c) # 0 1 2 3 4
  ```

- math

  ```python
  from math import ceil, floor, sqrt
  print(ceil(7/3))  # 3
  print(floor(7/3))  # 2
  print(floor(sqrt(121) + 0.1)) # 11
  print(pow(11, 2, 100)) # 21 (11^2 mod 100)
  ```

- gcd, lcm

  ```python
  from fractions import gcd
  def lcm(a, b):
      return (a * b) // gcd(a, b)
  print(lcm(3, 4), gcd(30, 45))
  ```

- collections

  ```python
  from collections import Counter
  l=['a','b','b','c','b','a','c','c','b','c','b','a']
  c=Counter(l) # カウンタークラスが作られる。S=Counter({'b': 5, 'c': 4, 'a': 3})
  print(c.most_common(2)) # [('b', 5), ('c', 4)]
  print(*c.keys()) # ['a', 'b', 'c']
  print(*c.values()) # [3, 5, 4]
  print(*c.items()) # [('a', 3), ('b', 5), ('c', 4)]
  ```

- list

  ```python
  l = list(range(-5, 6))
  a, b, *c = l  # 要素を途中から取り出す
  print(c) # [-3, -2, -1, 0, 1, 2, 3, 4, 5]
  print(l) # [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5]
  print([i for i in l if i % 2 == 1])  # 奇数だけ [-5, -3, -1, 1, 3, 5]
  
  a = [[(x, y) for x in range(4)] for y in range(3)]  # 4x3の配列初期化
  for i in range(3):
      for j in reversed(range(4)):
          print(a[i][j], i, j)
  ```

- permutations, combinations

  ```python
  from itertools import product, permutations, combination
  l = list(range(4))
  for x in product(l, repeat=3): # 全列挙
      print(x)
  for x in permutations(l, 3): # 順列
      print(x)
  for x in combinations(l, 3): # 組み合わせ
      print(x)
  ```

- sort, sorted, reversed

  ```python
  a = [1, 5, 3, 2, 4]
  print(sorted(a)) # [1, 2, 3, 4, 5]
  b = sorted(a, reverse=True)
  print(b) # [5, 4, 3, 2, 1]
  b.sort()
  print(b) # [1, 2, 3, 4, 5]
  ```

- groupby

  ```python
  from itertools import groupby
  a = [1, 3, 2, 4, 3, 1, 1, 2, 4]
  for key, value in groupby(a, key=lambda x: x % 2):
      print(key, list(value))
  ```

  