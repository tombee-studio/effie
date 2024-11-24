#include <lexer.hpp>
using namespace Effie;

void
testToken(string input, Type type) {
  auto tokens = Lexer::lex(input);
  assert(tokens[0].getType() == type);
}

int
main() {
  testToken("[", Type::KW_LBRACKET);
  testToken("]", Type::KW_RBRACKET);
  testToken(":", Type::KW_COLON);
  testToken(";", Type::KW_SEMICOLON);
  testToken(".", Type::KW_DOT);
  testToken(",", Type::KW_COMMA);
  testToken("(", Type::KW_LPAREN);
  testToken(")", Type::KW_RPAREN);
  testToken("+", Type::KW_ADD);
  testToken("-", Type::KW_SUB);
  testToken("*", Type::KW_MUL);
  testToken("/", Type::KW_DIV);
  testToken("%", Type::KW_MOD);
  testToken(">", Type::KW_GT);
  testToken("<", Type::KW_LT);
  testToken("==", Type::KW_EQ);
  testToken("!=", Type::KW_NE);
  testToken(">=", Type::KW_GE);
  testToken("<=", Type::KW_LE);
  testToken("!", Type::KW_NOT);
  testToken("\"Hello, World!\"", Type::STRING);
  testToken("\"こんにちは、世界。\"", Type::STRING);
  testToken("1", Type::INT);
  testToken("1234567890", Type::INT);
  testToken("1.01", Type::DOUBLE);
  testToken("123456789.0123456789", Type::DOUBLE);
  testToken("abc", Type::ID);
  return 0;
}
