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

struct Dinic {
  struct Edge {
    int to, cap, rev;
    Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
  };
  int V;
  std::vector<std::vector<Edge>> graph;
  std::vector<int> level, iter;

  Dinic(int v) : V(v) {
    graph.resize(v);
    level.resize(v, -1);
    iter.resize(v, 0);
  }
  // fromからtoへ向かう容量capの辺をグラフに追加する
  void addEdge(int from, int to, int cap) {
    graph[from].emplace_back(to, cap, graph[to].size());
    graph[to].emplace_back(from, 0, graph[from].size() - 1);
  }
  // sからの最短距離をBFSで計算する
  void bfs(int s) {
    std::fill(level.begin(), level.end(), -1);
    std::queue<int> queue;
    level[s] = 0;
    queue.push(s);
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (int i = 0; i < graph[v].size(); ++i) {
        Edge& e = graph[v][i];
        if (e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          queue.push(e.to);
        }
      }
    }
  }
  // 増加パスをDFSで探す
  int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < graph[v].size(); ++i) {
      Edge& e = graph[v][i];
      if (e.cap > 0 && level[v] < level[e.to]) {
        int d = dfs(e.to, t, std::min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          graph[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }
  // sからtへの最大流を求める
  int maxFlow(int s, int t) {
    int res = 0;
    while (true) {
      bfs(s);
      if (level[t] < 0) return res;
      std::fill(iter.begin(), iter.end(), 0);
      int f;
      while ((f = dfs(s, t, (1LL << 31) - 1)) > 0) {
        res += f;
      }
    }
  }
};

void solve() {
  Dinic di(5);
  di.addEdge(0, 1, 1);
  di.addEdge(0, 2, 2);
  di.addEdge(0, 3, 3);
  di.addEdge(1, 4, 3);
  di.addEdge(2, 4, 1);
  di.addEdge(3, 4, 5);
  dump(di.maxFlow(0, 4));
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  cout << fixed << setprecision(15);
  // freopen("temp.1", "r", stdin);
  solve();
  return 0;
}