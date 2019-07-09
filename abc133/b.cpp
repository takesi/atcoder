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

int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("temp.1", "r", stdin);

  int N, D;
  cin >> N >> D;
  vector<vector<int>> x(N, vector<int>(D));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < D; j++) {
      cin >> x[i][j];
    }
  }
  vector<int> f(40 * 40 * D + 1);
  dump((int)sqrt(f.size()) + 1);
  for (int i = 1; i < (int)sqrt(f.size()) + 1; i++) {
    if (i * i < f.size()) {
      f[i * i] = 1;
    }
  }
  int ans = 0;
  for (int i = 0; i < N - 1; i++) {
    for (int j = i; j < N; j++) {
      int sum = 0;
      for (int k = 0; k < D; k++) {
        int sub = abs(x[i][k] - x[j][k]);
        sum += (sub * sub);
      }
      if (f[sum])
        ans++;
    }
  }
  cout << ans << endl;
  return 0;
}