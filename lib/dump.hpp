#define dump(...) _dump(#__VA_ARGS__, __VA_ARGS__)
#define dumpv(...) _dumpv(#__VA_ARGS__, __VA_ARGS__)

template<typename T1, typename T2>
inline ostream& operator<<(ostream& o, const pair<T1, T2>& v)
{
  return o << v.first << "," << v.second;
}

template<typename T1, typename T2, typename T3>
inline ostream& operator<<(ostream& o, const tuple<T1, T2, T3>& v)
{
  return o << get<0>(v) << "," << get<1>(v) << "," << get<2>(v);
}

#define _dumpit(o, v) { o << "[ ";\
  for (auto it = v.begin(); it != v.end(); it++) { o << *it << " "; } o << "]"; }

template<typename T>
inline ostream& operator<<(ostream& o, const vector<T>& v) {
  _dumpit(o, v);
  return o;
}

template<typename T>
inline ostream& operator<<(ostream& o, const list<T>& v) {
  _dumpit(o, v);
  return o;
}

template<typename T>
inline ostream& operator<<(ostream& o, const queue<T>& v) {
  _dumpit(o, v);
  return o;
}

template<typename T>
inline ostream& operator<<(ostream& o, const set<T>& v) {
  _dumpit(o, v);
  return o;
}

template<typename T1, typename T2>
inline ostream& operator<<(ostream& o, const map<T1, T2>& v) {
  _dumpit(o, v);
  return o;
}

const char* _dumps(const char* s)
{
  int text = false;
  while (*s == ' ')
    s++;
  if (*s == '"')
    text = true;
  while (*s != ',' && *s != '\0') {
    if (!text)
      cerr << *s++;
    else
      s++;
  }
  if (!text)
    cerr << "=";
  return s;
}

template<typename T>
void _dump(const char* s, T&& head)
{
  s = _dumps(s);
  cerr << head << endl;
}

template<typename T, typename... Args>
void _dump(const char* s, T&& head, Args&&... tail)
{
  s = _dumps(s);
  cerr << head << ", ";
  _dump(s + 1, tail...);
}

template<typename T>
void _dumpv(const char* s, T&& v)
{
  s = _dumps(s);
  cerr << v << endl;
}

template<typename T>
void _dumpv(const char* s, T&& v, int n)
{
  s = _dumps(s);
  cerr << "[ ";
  for (int i = 0; i < n; i++) {
    cerr << v[i] << " ";
  }
  cerr << "]" << endl;
}

template<typename T>
void _dumpv(const char* s, T&& v, int n, int m)
{
  s = _dumps(s);
  cerr << "[" << n << "][" << m << "]" << endl;
  for (int i = 0; i < n; i++) {
    cerr << i << ": ";
    for (int j = 0; j < m; j++) {
      cerr << v[i][j] << " ";
    }
    cerr << endl;
  }
}

template<typename T, typename... Args>
void _dumpv(const char* s, T&& head, Args&&... tail)
{
  s = _dumps(s);
  cerr << head << ", ";
  _dumpv(s + 1, tail...);
}