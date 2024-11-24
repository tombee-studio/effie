#include <lexer.hpp>
#include <interpreter.hpp>
#include <initializer_list>
using namespace Effie;
using namespace std;

void
testToken(string input, Type type) {
  auto tokens = Lexer::lex(input);
  assert(tokens[0].getType() == type);

  cout << "OK!" << endl;
}

void
testInterpreter(initializer_list<MnemonicCode> array, ValueObject target) {
  vector<MnemonicCode> codes;
  for(int i = 0; i < array.size(); i++) {
    codes.push_back(*(array.begin() + i));
  }
  Interpreter interpreter;
  interpreter.setMnemonics(codes);
  interpreter.run();

  auto value = interpreter.getStack().top();
  assert(value.getType() == target.getType());
  switch(value.getType()) {
  case ValueType::INT:
    assert(value.getIntValue() == target.getIntValue());
    break;
  default:
    break;
  }
  cout << "OK!" << endl;
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

  testInterpreter({
    MnemonicCode(Mnemonic::POP),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(1)),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(2)),
    MnemonicCode(Mnemonic::ADD)
  }, ValueObject::createIntValue(3));
  return 0;
}
