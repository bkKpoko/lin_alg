#ifndef _NUM3_H_
#define _NUM3_H_

// #define _CHECKBOUNDS_ 0

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <initializer_list>
#include <stdexcept>
#include <string>

template <class T> class Nvector;
template <class T> class Nmatrix;

template <class T> inline void print(T &a, T &b, int prec = 2);
template <class T> inline void SWAP(T &a, T &b);
template <class T> inline void MAX(const Nmatrix<T> &a, int &i, int &j, T &el);
template <class T> inline void MAX(const Nmatrix<T> &a, T &el);
template <class T> inline void MAX(const Nmatrix<T> &a, int &i, int &j);
template <class T> inline T MAX(const T &a, const T &b);
template <class T> inline int CHARS_IN_VALUE(const T &a, const int &i);
template <class T> inline bool isNEGATIVE(T &a);

template <class T> class Nvector {
private:
  int nn;
  T *v;

public:
  Nvector();
  explicit Nvector(int n);
  Nvector(int n, const T &a);
  Nvector(int n, const T *a);
  Nvector(const Nvector &rhs);
  Nvector(const std::initializer_list<T> list);

  Nvector &operator=(const Nvector &rhs);
  typedef T value_type;
  inline T &operator[](const int i);
  inline const T &operator[](const int i) const;

  inline int size() const;
  void resize(int newn);
  void assign(int newn, const T &a);

  ~Nvector();
};

template <class T> Nvector<T>::Nvector() : nn(0), v(NULL) {}

template <class T>
Nvector<T>::Nvector(int n) : nn(n), v(n > 0 ? new T[n] : NULL) {}

template <class T>
Nvector<T>::Nvector(int n, const T &a) : nn(n), v(n > 0 ? new T[n] : NULL) {
  for (int i = 0; i < n; ++i)
    v[i] = a;
}

template <class T>
Nvector<T>::Nvector(int n, const T *a) : nn(n), v(n > 0 ? new T[n] : NULL) {
  for (int i = 0; i < n; ++i)
    v[i] = *a++;
}

template <class T>
Nvector<T>::Nvector(const Nvector<T> &rhs)
    : nn(rhs.nn), v(nn > 0 ? new T[nn] : NULL) {
  for (int i = 0; i < nn; ++i)
    v[i] = rhs[i];
}

template <class T>
Nvector<T>::Nvector(const std::initializer_list<T> list)
    : nn(list.size()), v(nn > 0 ? new T[nn] : NULL) {
  int i = 0;
  for (const T &val : list) {
    v[i] = val;
    ++i;
  }
}

template <class T> Nvector<T> &Nvector<T>::operator=(const Nvector<T> &rhs) {
  if (this != &rhs) {
    if (nn != rhs.nn) {
      nn = rhs.nn;
      if (v != NULL)
        delete[] (v);
      v = nn > 0 ? new T[nn] : NULL;
    }
    for (int i = 0; i < nn; ++i) {
      v[i] = rhs[i];
    }
  }
  return *this;
}

template <class T> inline T &Nvector<T>::operator[](const int i) {
#ifdef _CHECKBOUNDS_
  if (i >= nn || i < 0) {
    throw std::runtime_error("index out of bounds");
  }
#endif // _CHECKBOUNDS_
  return v[i];
}

template <class T> inline const T &Nvector<T>::operator[](const int i) const {
#ifdef _CHECKBOUNDS_
  if (i >= nn || i < 0) {
    throw std::runtime_error("index out of bounds");
  }
#endif // _CHECKBOUNDS_
  return v[i];
}

template <class T> inline int Nvector<T>::size() const { return nn; }

template <class T> void Nvector<T>::resize(int newn) {
  if (nn != newn) {
    if (v != NULL)
      delete[] (v);
    nn = newn;
    v = nn > 0 ? new T[nn] : NULL;
  }
}

template <class T> void Nvector<T>::assign(int newn, const T &a) {
  if (newn != nn) {
    if (v != NULL)
      delete[] (v);
    nn = newn;
    if (nn > 0)
      for (int i = 0; i < nn; i++)
        v[i] = a;
  }
}

template <class T> Nvector<T>::~Nvector() {
  if (v != NULL)
    delete[] (v);
}

template <class T> class Nmatrix {
private:
  int nn;
  int mm;
  T **v;

public:
  Nmatrix();
  Nmatrix(int n, int m);
  Nmatrix(int n, int m, const T &a);
  Nmatrix(int n, int m, const T *a);
  Nmatrix(std::initializer_list<std::initializer_list<T>> matrix);
  Nmatrix(const Nmatrix &rhs);

  Nmatrix &operator=(const Nmatrix &rhs);
  typedef T value_type;
  inline T *operator[](const int i);
  inline const T *operator[](const int i) const;

  inline int nrows() const;
  inline int ncols() const;
  void resize(int newn, int newm);
  void assign(int newn, int newm, const T &a);

  void char_elem_matr(Nmatrix<int> &m, const int &n) const;
  void print(const int prec = 2);

  ~Nmatrix();
};

template <class T> Nmatrix<T>::Nmatrix() : nn(0), mm(0), v(NULL) {}

template <class T>
Nmatrix<T>::Nmatrix(int n, int m) : nn(n), mm(m), v(n > 0 ? new T *[n] : NULL) {
  int i, nel = m * n;
  if (v)
    v[0] = nel > 0 ? new T[nel] : NULL;
  for (i = 1; i < n; ++i)
    v[i] = v[i - 1] + m;
}

template <class T>
Nmatrix<T>::Nmatrix(int n, int m, const T &a)
    : nn(n), mm(m), v(n > 0 ? new T *[n] : NULL) {
  int i, j, nel = m * n;
  if (v)
    v[0] = nel > 0 ? new T[nel] : NULL;
  for (i = 1; i < n; ++i)
    v[i] = v[i - 1] + m;
  for (i = 0; i < nn; ++i)
    for (j = 0; j < mm; ++j)
      v[i][j] = a;
}

template <class T>
Nmatrix<T>::Nmatrix(int n, int m, const T *a)
    : nn(n), mm(m), v(n > 0 ? new T *[n] : NULL) {
  int i, j, nel = m * n;
  if (v)
    v[0] = nel > 0 ? new T[nel] : NULL;
  for (i = 1; i < n; ++i)
    v[i] = v[i - 1] + m;
  for (i = 0; i < nn; ++i)
    for (j = 0; j < mm; ++j)
      v[i][j] = *a++;
}

template <class T>
Nmatrix<T>::Nmatrix(std::initializer_list<std::initializer_list<T>> matrix)
    : nn(matrix.size()), mm(matrix.begin()->size()),
      v(nn > 0 ? new T *[nn] : NULL) {
  int i, j, nel = mm * nn;
  if (v)
    v[0] = nel > 0 ? new T[nel] : NULL;
  for (i = 1; i < nn; ++i) {
    v[i] = v[i - 1] + mm;
  }

  i = 0;
  for (const auto &row : matrix) {
    j = 0;
    for (const auto &val : row) {
      v[i][j] = val;
      ++j;
    }
    ++i;
  }
}

template <class T>
Nmatrix<T>::Nmatrix(const Nmatrix &rhs)
    : nn(rhs.nn), mm(rhs.mm), v(nn > 0 ? new T *[nn] : NULL) {
  int i, j, nel = nn * mm;
  if (v)
    v[0] = nel > 0 ? new T[nel] : NULL;
  for (i = 1; i < nn; ++i)
    v[i] = v[i - 1] + mm;
  for (i = 0; i < nn; ++i)
    for (j = 0; j < mm; ++j)
      v[i][j] = rhs[i][j];
}

template <class T> Nmatrix<T> &Nmatrix<T>::operator=(const Nmatrix<T> &rhs) {
  if (this != &rhs) {
    int i, j, nel;
    if (nn != rhs.nn || mm != rhs.mm) {
      if (v != NULL) {
        delete[] v[0];
        delete[] (v);
      }
      nn = rhs.nn;
      mm = rhs.mm;
      v = nn > 0 ? new T *[nn] : NULL;
      nel = mm * nn;
      if (v)
        v[0] = nel > 0 ? new T[nel] : NULL;
      for (i = 0; i < nn; ++i)
        v[i] = v[i - 1] + mm;
    }
    for (i = 1; i < nn; ++i)
      for (j = 0; j < mm; ++j)
        v[i][j] = rhs[i][j];
  }
  return *this;
}

template <class T> inline T *Nmatrix<T>::operator[](const int i) {
#ifdef _CHECKBOUNDS_
  if (i < 0 || i >= nn)
    throw std::runtime_error("index out of bounds");
#endif // _CHECKBOUNDS_
  return v[i];
}

template <class T> inline const T *Nmatrix<T>::operator[](const int i) const {
#ifdef _CHECKBOUNDS_
  if (i < 0 || i >= nn)
    throw std::runtime_error("index out of bounds");
#endif // _CHECKBOUNDS_
  return v[i];
}

template <class T> inline int Nmatrix<T>::nrows() const { return nn; }

template <class T> inline int Nmatrix<T>::ncols() const { return mm; }

template <class T> void Nmatrix<T>::resize(int newn, int newm) {
  if (nn != newn || mm != newm) {
    int i, nel;
    if (v != NULL) {
      delete[] v[0];
      delete[] (v);
    }
    nn = newn;
    mm = newm;
    v = nn > 0 ? new T *[nn] : NULL;
    nel = nn * mm;
    if (v)
      v[0] = nel > 0 ? new T[nel] : NULL;
    for (i = 1; i < nn; ++i)
      v[i] = v[i - 1] + mm;
  }
}

template <class T> void Nmatrix<T>::assign(int newn, int newm, const T &a) {
  int i, j, nel;
  if (nn != newn || mm != newm) {
    if (v != NULL) {
      delete[] v[0];
      delete[] (v);
    }
    nn = newn;
    mm = newm;
    v = nn > 0 ? new T *[nn] : NULL;
    nel = nn * mm;
    if (v)
      for (i = 1; i < nn; ++i)
        v[i] = v[i - 1] + mm;
  }
  for (i = 0; i < nn; ++i)
    for (j = 0; j < mm; ++j)
      v[i][j] = a;
}

template <class T> void Nmatrix<T>::print(const int prec) {
  T el;
  bool is_negative;
  int max_size;
  Nmatrix<int> char_sizes;
  char_elem_matr(char_sizes, prec);
  MAX(char_sizes, max_size);

  std::string s = "";
  for (size_t i = 0; i < nn; i++) {
    s += "| ";
    for (size_t j = 0; j < mm; j++) {
      el = v[i][j];
      is_negative = isNEGATIVE(el);
      s += is_negative ? "" : " ";
      s += std::to_string(el).substr(0, char_sizes[i][j] + is_negative) + " ";
      for (size_t t = 0; t < max_size - char_sizes[i][j]; t++)
        s += " ";
    }
    s += " |\n";
  }
  puts(s.c_str());
}

template <class T>
void Nmatrix<T>::char_elem_matr(Nmatrix<int> &m, const int &n) const {
  if (m.ncols() != mm || m.nrows() != nn)
    m.resize(nn, mm);

  for (size_t i = 0; i < nn; i++) {
    for (size_t j = 0; j < mm; j++) {
      m[i][j] = CHARS_IN_VALUE(v[i][j], n);
    }
  }
}

template <class T> Nmatrix<T>::~Nmatrix() {
  if (v != NULL) {
    delete[] v[0];
    delete[] (v);
  }
}

template <class T> inline void print(T &a, T &b, int prec) {
  if (a.nrows() != b.nrows()) {
    puts("Matrix sizes are incompatible");
    return;
  }
  std::string s = "";
  typename T::value_type el;
  bool is_negative;
  int max, max_a, max_b;
  Nmatrix<int> char_a;
  Nmatrix<int> char_b;

  a.char_elem_matr(char_a, prec);
  b.char_elem_matr(char_b, prec);

  MAX(char_a, max_a);
  MAX(char_b, max_b);

  max = MAX(max_a, max_b);

  for (size_t i = 0; i < a.nrows(); i++) {
    s += "| ";
    for (size_t j = 0; j < a.ncols(); j++) {
      el = a[i][j];
      is_negative = isNEGATIVE(el);
      s += is_negative ? "" : " ";
      s += std::to_string(el).substr(0, char_a[i][j] + is_negative) + " ";
      for (size_t t = 0; t < max - char_a[i][j]; t++)
        s += " ";
    }
    s += " || ";
    for (size_t j = 0; j < b.ncols(); j++) {
      el = b[i][j];
      is_negative = isNEGATIVE(el);
      s += is_negative ? "" : " ";
      s += std::to_string(el).substr(0, char_b[i][j] + is_negative) + " ";
      for (size_t t = 0; t < max - char_b[i][j]; t++)
        s += " ";
    }
    s += " |\n";
  }
  puts(s.c_str());
}

template <class T> inline void SWAP(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <class T> inline void MAX(const Nmatrix<T> &a, int &i, int &j, T &el) {
  el = NULL;
  for (size_t x = 0; x < a.nrows(); x++) {
    for (size_t y = 0; y < a.ncols(); y++) {
      el = el < a[x][y] ? a[x][y] : el;
      i = x;
      j = y;
    }
  }
}

template <class T> inline void MAX(const Nmatrix<T> &a, T &el) {
  el = NULL;
  for (size_t x = 0; x < a.nrows(); x++) {
    for (size_t y = 0; y < a.ncols(); y++) {
      el = el < a[x][y] ? a[x][y] : el;
    }
  }
}

template <class T> inline void MAX(const Nmatrix<T> &a, int &i, int &j) {
  T el = NULL;
  for (size_t x = 0; x < a.nrows(); x++) {
    for (size_t y = 0; y < a.ncols(); y++) {
      el = el < a[x][y] ? a[x][y] : el;
      i = x;
      j = y;
    }
  }
}

template <class T> inline T MAX(const T &a, const T &b) {
  return a > b ? a : b;
}

template <class T> inline int CHARS_IN_VALUE(const T &a, const int &i) {
  int x = int(abs(a));
  return x > 0 ? log10(x) + i + 2 : 2 + i;
}

template <class T> inline bool isNEGATIVE(T &a) { return a < 0; }

#endif // !_NUM3_H_
