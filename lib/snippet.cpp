// to[]の木構築
vector<vector<int>> to(N);
for (int i = 0; i < N - 1; i++) {
  int u, v;
  cin >> u >> v;
  u--, v--;
  to[u].push_back(v);
  to[v].push_back(u);
}

// BFSのスニペット (to[]の木探索)
queue<int> q;
vector<int> used(N);
q.push(0);
while (!q.empty()) {
  int v = q.front();
  q.pop();
  if (used[v])
    continue;
  used[v] = 1;
  for (auto& u : to[v]) {
    q.push(u);
  }
}

// DFSのスニペット (to[]の木探索)
vector<int> used(N);
function<void(int, int)> dfs = [&](int v, int from) {
  if (used[v])
    return;
  used[v] = 1;
  for (auto& u : to[v]) {
    dfs(u, v);
  }
};
dfs(0, -1);

// mintのスニペット (最低限の処理のみ)
struct mint
{
  ll v;
  mint() : v(0) {}
  mint(ll v) : v((v % MOD + MOD) % MOD) {}
};
mint& operator+=(mint& a, mint b) { return a = a.v + b.v; }
mint& operator-=(mint& a, mint b) { return a = a.v - b.v; }
mint& operator*=(mint& a, mint b) { return a = a.v * b.v; }
mint operator+(mint a, mint b) { return a += b; }
mint operator-(mint a, mint b) { return a -= b; }
mint operator*(mint a, mint b) { return a *= b; }
mint operator-(mint a) { return 0 - a; }

// n進数vectorのスニペット (最低限の実装のみ)
struct nvec : public vector<int>
{
  int base;
  nvec(int len, int base) : vector<int>(len), base(base) {}
  nvec& operator++()
  {
    for (int i = 0; i < size(); i++) {
      at(i)++;
      if (at(i) < base)
        break;
      at(i) = 0;
    }
    return *this;
  };
  nvec& operator++(int dummy) { return operator++(); };
};