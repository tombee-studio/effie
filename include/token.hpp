#pragma once
#include <utils.hpp>
#include <cstring>
#include <type.hpp>

namespace Effie {
  class Token {
    GETTER(Type, Type, Type::NONE)
    GETTER(string, Id, "")
    GETTER(string, StringVal, "")
    GETTER(int, IntVal, 0)
    GETTER(double, DoubleVal, 0.0)
    
    Token() {}
  public:

    static Token createIdToken(string);
    static Token createStringToken(string);
    static Token createIntToken(int);
    static Token createDoubleToken(double);
    static Token createKeywordToken(Type);
    static Token createNone();
  };
};
