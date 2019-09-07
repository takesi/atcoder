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

void solve() {
  int N, M;
  cin >> N >> M;
  vector<vector<int>> dist(N, vector<int>(N, INF)); // dist[from][to]
  for (int i = 0; i < N; i++) {
    dist[i][i] = 0; // 自分自身へは距離0
  }
  for (int i = 0; i < M; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    dist[u][v] = c;
    dist[v][u] = c; // 無向辺の場合は両側に入力
  }
  for (int k = 0; k < N; k++) {     // 経由する頂点
    for (int i = 0; i < N; i++) {   // 開始頂点
      for (int j = 0; j < N; j++) { // 終端
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        // 経路復元をしたい場合は経由頂点を更新時に覚えて後で再帰的にたどる
      }
    }
  }
  // 最小コストを表示
  for (int i = 0; i < N; i++) { // 開始頂点
    cout << i + 1 << " to ";
    for (int j = 0; j < N; j++) { // 終端
      if (i != j && dist[i][j] != INF) cout << j + 1 << ":" << dist[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  freopen((string(__FILE__) + ".1").c_str(), "r", stdin);
  solve();
  return 0;
}