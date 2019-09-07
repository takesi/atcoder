#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "dump.hpp"
#else
#define dump(...)
#define dumpv(...)
#endif

typedef long long ll;
typedef pair<int, int> P;
const int MOD = 1e9 + 7;
const int INF = 1001001001;
const ll LINF = 1001002003004005006ll;

struct RollingHash {
  const int nmod = 2;
  using hash_type = tuple<ll, ll>; // 衝突が起こるようならmodを増やして

  vector<ll> base{ 1009, 1007 };                // 2339, 9973 など
  vector<ll> mod{ 1000000007LL, 1000000009LL }; // 1000000087LL, 999999937LL など
  vector<vector<ll>> hash;
  vector<vector<ll>> pow;

  RollingHash() {
    hash.resize(nmod);
    pow.resize(nmod);
  }

  // 文字列からハッシュテーブルを作成する
  void init(const string& s) {
    int n = s.size();
    for (int j = 0; j < nmod; j++) {
      hash[j].assign(n + 1, 0);
      pow[j].assign(n + 1, 1);
      for (int i = 0; i < n; i++) {
        hash[j][i + 1] = (hash[j][i] + s[i]) * base[j] % mod[j];
        pow[j][i + 1] = pow[j][i] * base[j] % mod[j];
      }
    }
  }
  // ハッシュ値を返す [l, r) : 例えばget(0, len)は先頭len文字
  hash_type get(int l, int r) {
    ll h[nmod];
    for (int j = 0; j < nmod; j++) {
      h[j] = ((hash[j][r] - hash[j][l] * pow[j][r - l]) % mod[j] + mod[j]) % mod[j];
    }
    return make_tuple(h[0], h[1]);
  }
  // ハッシュ値h1に長さh2_lenのハッシュ値h2を結合する
  hash_type concat(hash_type h1, hash_type h2, int h2_len) {
    ll h[nmod];
    h[0] = (std::get<0>(h1) * pow[0][h2_len] + std::get<0>(h2)) % mod[0];
    h[1] = (std::get<1>(h1) * pow[1][h2_len] + std::get<1>(h2)) % mod[1];
    return make_tuple(h[0], h[1]);
  }
};

// 型の名前が長いので省略名を定義
using hs = RollingHash::hash_type;

void solve() {
  string s = "abcabcabc";
  RollingHash rh;
  rh.init(s);
  dump("abcabcabc", rh.get(0, s.length()));
  hs h1 = rh.get(0, 3);
  hs h2 = rh.get(3, 6);
  hs h3 = rh.get(6, 9);
  hs hall = rh.concat(h1, h2, 3);
  hall = rh.concat(hall, h3, 3);
  dump(h1, h2, h3, hall, rh.get(0, s.length()));
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  cout << fixed << setprecision(15);
  // freopen("temp.1", "r", stdin);
  solve();
  return 0;
}