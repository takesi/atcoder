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

void solve() // 最短距離と経路も表示
{
  int N, M;
  cin >> N >> M;
  vector<vector<int>> to(N);
  vector<vector<int>> co(N);
  for (int i = 0; i < M; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--;
    v--;
    to[u].push_back(v);
    co[u].push_back(c);
    to[v].push_back(u);
    co[v].push_back(c);
  }
  int start = 1; // スタート
  int end = 5;   // ゴール
  start--, end--;
  dump(to);
  dump(co);
  vector<P> dist(N, P(INF, -1)); // P(dist, from)
  priority_queue<P, vector<P>, greater<P>> q; // P(cost, v)
  dist[start] = P(0, -1);
  q.push(P(0, start));
  while (!q.empty()) {
    P p = q.top();
    q.pop();
    int u = p.second;
    if (dist[u].first < p.first) continue;
    rep(i, to[u].size()) {
      int v = to[u][i], c = co[u][i];
      if (dist[v].first > dist[u].first + c) {
        dist[v] = P(dist[u].first + c, u);
        q.push(P(dist[v].first, v));
      }
    }
  }
  dump(dist);
  int v = end;
  // 最小コストを表示
  cout << dist[v].first << endl;
  // 経路をゴールからスタートにたどる
  while (v != -1) {
    cout << v << " ";
    v = dist[v].second;
  }
  cout << endl;
}

struct E {
  int to;
  int co;
  E(int to, int co) : to(to), co(co) {}
};
inline ostream& operator<<(ostream& o, const E& v) { return o << v.to << "," << v.co; }

void solve2() // 最短距離と経路も表示 (構造体)
{
  int N, M;
  cin >> N >> M;
  vector<vector<E>> to(N);
  for (int i = 0; i < M; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--;
    v--;
    to[u].emplace_back(v, c);
    to[v].emplace_back(u, c);
  }
  int start = 1; // スタート
  int end = 5;   // ゴール
  dump(to);
  vector<P> dist(N); // dist, from
  dist.assign(N, P(INF, -1));
  priority_queue<P, vector<P>, greater<P>> q; // cost, v
  int s = start - 1;
  dist[s] = P(0, -1);
  q.push(P(0, s));
  while (!q.empty()) {
    P p = q.top();
    q.pop();
    int v = p.second;
    if (dist[v].first < p.first) continue;
    for (int i = 0; i < to[v].size(); ++i) {
      E e = to[v][i];
      if (dist[e.to].first > dist[v].first + e.co) {
        dist[e.to] = P(dist[v].first + e.co, v);
        q.push(P(dist[e.to].first, e.to));
      }
    }
  }
  dump(dist);
  int v = end - 1;
  // 最小コストを表示
  cout << dist[v].first << endl;
  // 経路をゴールからスタートにたどる
  while (v != -1) {
    cout << v << " ";
    v = dist[v].second;
  }
  cout << endl;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  freopen((string(__FILE__) + ".1").c_str(), "r", stdin);
  solve();
  freopen((string(__FILE__) + ".1").c_str(), "r", stdin);
  solve2();
  return 0;
}