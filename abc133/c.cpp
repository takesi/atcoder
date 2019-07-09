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
// const int MOD = 1e9 + 7;
const ll MOD = 2019;
const int INF = 1001001001;
const ll LINF = 1001002003004005006ll;

int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("temp.1", "r", stdin);

  ll L, R;
  cin >> L >> R;
  L = L % MOD;
  R = R % MOD;
  dump(L, R);
  ll ans = LINF;
  if (R < L)
    swap(R, L);
  for (int i = L; i < R; i++) {
    for (int j = (i + 1) % MOD; j <= R; j++) {
      ans = min(ans, (i * j) % MOD);
    }
  }
  cout << ans << endl;
  return 0;
}