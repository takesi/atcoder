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

  int N;
  cin >> N;
  vector<ll> a(N);
  vector<ll> m(N);
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }
  ll rain = a[0];
  for (int j = 1; j < N; j++) {
    if (j % 2 == 1)
      rain -= a[(0 + j) % N];
    else
      rain += a[(0 + j) % N];
  }
  m[0] = rain;
  for (int i = 1; i < N; i++) {
    m[i] = (a[i - 1] - m[i - 1] / 2) * 2;
  }
  for (int i = 0; i < N; i++) {
    cout << m[i] << " ";
  }
  cout << endl;
  return 0;
}