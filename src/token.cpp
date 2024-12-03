#include <token.hpp>
using namespace Effie;

Token
Token::createIdToken(string id) {
  Token token;
  token.setType(Type::ID);
  token.setId(id);
  return token;
}

Token
Token::createStringToken(string value) {
  Token token;
  token.setType(Type::STRING);
  token.setStringVal(value);
  return token;
}

Token
Token::createIntToken(int value) {
  Token token;
  token.setType(Type::INT);
  token.setIntVal(value);
  return token;
}

Token
Token::createDoubleToken(double value) {
  Token token;
  token.setType(Type::DOUBLE);
  token.setDoubleVal(value);
  return token;
}

Token
Token::createKeywordToken(Type type) {
  Token token;
  token.setType(type);
  return token;
}

Token
Token::createNone() {
  Token token;
  token.setType(Type::NONE);
  return token;
}
