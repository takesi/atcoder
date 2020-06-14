#define dump(...) _dump(#__VA_ARGS__, __VA_ARGS__)
#define dumpv(...) _dumpv(#__VA_ARGS__, __VA_ARGS__)

#ifndef console
#define console cerr
#endif

template<typename T>
class _vector : public vector<T> {
public:
  _vector() : vector<T>() {}
  explicit _vector(size_t n, const T& value = T()) : vector<T>(n, value) {}
  _vector(const vector<T>& v) : vector<T>(v) {}
  T& operator[](size_t n) {
    if (n < 0 || this->size() <= n) {
      console << n << " is out of [0:" << this->size() - 1 << "]\n";
    }
    return this->at(n);
  }
};
#define vector _vector
#define bool int

template<typename T>
inline ostream& operator<<(ostream& o, const vector<T>& v);
template<typename T>
inline ostream& operator<<(ostream& o, const list<T>& v);
template<typename T>
inline ostream& operator<<(ostream& o, const queue<T>& v);
template<typename T>
inline ostream& operator<<(ostream& o, const deque<T>& v);
template<typename T>
inline ostream& operator<<(ostream& o, const set<T>& v);
template<typename T>
inline ostream& operator<<(ostream& o, const unordered_set<T>& v);
template<typename T>
inline ostream& operator<<(ostream& o, const multiset<T>& v);
template<typename T1, typename T2>
inline ostream& operator<<(ostream& o, const map<T1, T2>& v);
template<typename T1, typename T2>
inline ostream& operator<<(ostream& o, const unordered_map<T1, T2>& v);

template<typename T1, typename T2>
inline ostream& operator<<(ostream& o, const pair<T1, T2>& v) {
  return o << v.first << "," << v.second;
}

template<typename T1, typename T2>
inline ostream& operator<<(ostream& o, const tuple<T1, T2>& v) {
  return o << get<0>(v) << "," << get<1>(v);
}

template<typename T1, typename T2, typename T3>
inline ostream& operator<<(ostream& o, const tuple<T1, T2, T3>& v) {
  return o << get<0>(v) << "," << get<1>(v) << "," << get<2>(v);
}

#define _dumpit(o, v) { o << "[ "; for (auto it = v.begin(); it != v.end(); it++) { o << *it << " "; } o << "]"; }

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
inline ostream& operator<<(ostream& o, const deque<T>& v) {
  _dumpit(o, v);
  return o;
}

template<typename T>
inline ostream& operator<<(ostream& o, const set<T>& v) {
  _dumpit(o, v);
  return o;
}

template<typename T>
inline ostream& operator<<(ostream& o, const unordered_set<T>& v) {
  _dumpit(o, v);
  return o;
}

template<typename T>
inline ostream& operator<<(ostream& o, const multiset<T>& v) {
  _dumpit(o, v);
  return o;
}

template<typename T1, typename T2>
inline ostream& operator<<(ostream& o, const map<T1, T2>& v) {
  _dumpit(o, v);
  return o;
}

template<typename T1, typename T2>
inline ostream& operator<<(ostream& o, const unordered_map<T1, T2>& v) {
  _dumpit(o, v);
  return o;
}

const char* _dumps(const char* s) {
  int text = false;
  int stack = 0;
  while (*s == ' ') s++;
  if (*s == '"') text = true;
  while (*s != '\0') {
    if (*s == '(')
      stack++;
    else if (*s == ')')
      stack--;
    else if (stack == 0 && *s == ',')
      break;
    if (!text)
      console << *s++;
    else
      s++;
  }
  if (!text) console << "=";
  return s;
}

template<typename T>
void _dump(const char* s, T&& head) {
  s = _dumps(s);
  console << head << endl;
}

template<typename T, typename... Args>
void _dump(const char* s, T&& head, Args&&... tail) {
  s = _dumps(s);
  console << head << ", ";
  _dump(s + 1, tail...);
}

template<typename T>
void _dumpv(const char* s, T&& v) {
  s = _dumps(s);
  console << v << endl;
}

template<typename T>
void _dumpv(const char* s, T&& v, int n) {
  s = _dumps(s);
  console << "[ ";
  for (int i = 0; i < n; i++) {
    console << v[i] << " ";
  }
  console << "]" << endl;
}

template<typename T>
void _dumpv(const char* s, T&& v, int n, int m) {
  s = _dumps(s);
  console << "[" << n << "][" << m << "]" << endl;
  for (int i = 0; i < n; i++) {
    console << i << ": ";
    for (int j = 0; j < m; j++) {
      console << v[i][j] << " ";
    }
    console << endl;
  }
}

template<typename T, typename... Args>
void _dumpv(const char* s, T&& head, Args&&... tail) {
  s = _dumps(s);
  console << head << ", ";
  _dumpv(s + 1, tail...);
}