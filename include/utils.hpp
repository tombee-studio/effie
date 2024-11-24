#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#ifdef DEBUG
#define debugPrint(x,...) printf(x,__VA_ARGS__)
#else
#define debugPrint(x,...)
#endif

#define PROPERTY(T, x, d) private:\
  T _##x = d;\
  string _propertyNameOf##x = #x;\
  public:\
  T& get##x() { return _##x; }\
  void set##x(T value) { _##x = value; }\
  string propertyNameOf##x() {\
    static string propertyName = _propertyNameOf##x;\
    propertyName[0] = tolower(_propertyNameOf##x[0]);\
    return propertyName;\
  }

#define GETTER(T, x, d) private:\
  T _##x = d;\
  string propertyNameOf##x = #x;\
  void set##x(T value) { _##x = value; }\
  public:\
  T& get##x() { return _##x; }\
  string propertyNameOf##x() {\
    static string propertyName = _propertyNameOf##x;\
    propertyName[0] = tolower(_propertyNameOf##x[0]);\
    return propertyName;\
  }

#define PRIVATE_PROPERTY(T, x, d) private:\
  T _##x = d;\
  string propertyNameOf##x = #x;\
  void set##x(T value) { _##x = value; }\
  T& get##x() { return _##x; }\
  public:\
  string propertyNameOf##x() {\
    static string propertyName = _propertyNameOf##x;\
    propertyName[0] = tolower(_propertyNameOf##x[0]);\
    return propertyName;\
  }
