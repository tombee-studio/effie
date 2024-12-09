#pragma once
#include <utils.hpp>
#include <vector>
#include <cstdlib>
#include <token.hpp>
using namespace std;

namespace Effie {
  class Lexer {
    string _text;
    const char *_cText;
    int _index;
    vector<Token> tokens;
  public:
    Lexer(string text): _text(text), _index(0) {
      _cText = text.data();
    }

    vector<Token> lex();
  private:
    bool skipSpace();
    bool lexKW(string keyword, Type type);
    bool lexInt();
    bool lexDouble();
    bool lexId();
    bool lexString();

    bool isIdentifier(char);
    bool isNumber(char);
  };
};
