#pragma once
#include <utils.hpp>
#include <vector>
#include <cstdlib>
#include <token.hpp>
using namespace std;

namespace Effie {
  class Lexer {
  public:
    static vector<Token> lex(string text);
  private:
    static bool skipSpace(const char *, int& start);
    static bool lexKW(vector<Token>& tokens, const char *, int& start, string keyword, Type type);
    static bool lexInt(vector<Token>& tokens, const char *, int& start);
    static bool lexDouble(vector<Token>& tokens, const char *, int& start);
    static bool lexId(vector<Token>& tokens, const char *, int& start);
    static bool lexString(vector<Token>& tokens, const char *, int& start);
  };
};
