/*
順列と組み合わせの列挙サンプル
 */
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
const ll MOD = 1e9 + 7;
const int INF = 1001001001;
const ll LINF = 1001002003004005006ll;

template<class Iter>
inline bool next_permutation2(Iter first, Iter k, Iter last) {
  if (first == k) return false;
  if (k == last) return next_permutation(first, last);
  Iter i = k;
  --i;
  if (*i < *k) {
    std::rotate(i, k, last);
    return true;
  }
  while (i != first) {
    Iter j = i;
    ++j;
    std::rotate(i, j, last);
    --i, --j;
    for (; j != last; ++j) {
      if (*i < *j) break;
    }
    if (j != last) {
      std::iter_swap(i, j);
      return true;
    }
  }
  std::rotate(first, ++Iter(first), last);
  return false;
}

template<typename Iter>
inline bool next_combination(Iter first, Iter k, Iter last) {
  if ((first == last) || (first == k) || (last == k)) return false;
  Iter it1 = first, it2 = last;
  ++it1;
  if (last == it1) return false;
  it1 = last;
  --it1;
  it1 = k;
  --it2;
  while (first != it1) {
    if (*--it1 < *it2) {
      Iter j = k;
      while (!(*it1 < *j)) ++j;
      std::iter_swap(it1, j);
      ++it1, ++j;
      it2 = k;
      std::rotate(it1, j, last);
      while (last != j) {
        ++it2, ++j;
      }
      std::rotate(k, it2, last);
      return true;
    }
  }
  std::rotate(first, k, last);
  return false;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("temp.1", "r", stdin);

  int n, k, c;
  cin >> n >> k;
  vector<int> v(n);
  iota(v.begin(), v.end(), 1);

  cout << "permutation:" << n << "P" << k << endl;
  c = 0;
  do {
    dumpv(v);
    c++;
  } while (next_permutation2(v.begin(), v.begin() + k, v.end()));
  cout << "total:" << c << endl;

  dumpv(v);
  cout << "combination:" << n << "C" << k << endl;
  c = 0;
  do {
    dumpv(v, k);
    c++;
  } while (next_combination(v.begin(), v.begin() + k, v.end()));
  cout << "total:" << c << endl;

  return 0;
}
