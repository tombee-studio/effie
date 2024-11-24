#pragma once
#include <utils.hpp>
#include <cstring>
#include <type.hpp>

namespace Effie {
  class Token {
    PROPERTY(Type, Type, Type::NONE)
    PROPERTY(string, Id, "")
    PROPERTY(string, StringVal, "")
    PROPERTY(int, IntVal, 0)
    PROPERTY(double, DoubleVal, 0.0)
    
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
