#include <lexer.hpp>
#include <parser.hpp>
#include <interpreter.hpp>
#include <initializer_list>
using namespace Effie;
using namespace std;

void
testToken(string input, Type type) {
  auto tokens = Lexer(input).lex();
  assert(tokens[0].getType() == type);

  cout << "OK! " << input << endl;
}

void
testLex(string input, initializer_list<Type> tokenTypes) {
  auto tokens = Lexer(input).lex();
  assert(tokens.size() == tokenTypes.size());
  for(int i = 0; i < tokenTypes.size(); i++) {
    auto targetTokenType = *(tokenTypes.begin() + i);
    assert(tokens[i].getType() == targetTokenType);
  }
  cout << "OK! " << input << endl;
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

void
testParser(string text) {
  auto tokens = Lexer(text).lex();
  Parser parser(tokens);
  auto root = parser.parse();
  cout << "OK! " << text << endl;
}

void
testInterpreterRun(string source, ValueObject target) {
  auto tokens = Lexer(source).lex();
  Parser parser(tokens);
  auto root = parser.parse();
  vector<MnemonicCode> codes;
  root->compile(codes);
  Interpreter interpreter;
  interpreter.setMnemonics(codes);
  interpreter.run();
  assert(interpreter.getReturnValue().eq(target).getIntValue() == 1);
  cout << "OK! " << source << endl;
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
  testToken("true", Type::KW_TRUE);
  testToken("false", Type::KW_FALSE);

  testLex("abc abc abc", { Type::ID, Type::ID, Type::ID });
  testLex("abc 1000 1234567890.0123456789", { Type::ID, Type::INT, Type::DOUBLE });
  testLex(
    "(1, 10.3, 1)", 
    { Type::KW_LPAREN, Type::INT, Type::KW_COMMA, Type::DOUBLE, Type::KW_COMMA, Type::INT, Type::KW_RPAREN });
  testLex(
    ">=><=<!+-*/%!====", 
    { Type::KW_GE, Type::KW_GT, Type::KW_LE, Type::KW_LT, Type::KW_NOT, Type::KW_ADD,
      Type::KW_SUB, Type::KW_MUL, Type::KW_DIV, Type::KW_MOD, Type::KW_NE, Type::KW_EQ, Type::KW_EQUAL });
  testLex(
    "a = \"Hello, World!\";",
    { Type::ID, Type::KW_EQUAL, Type::STRING, Type::KW_SEMICOLON }
  );
  testLex(
    "obj[\"引数\"]",
    { Type::ID, Type::KW_LBRACKET, Type::STRING, Type::KW_RBRACKET }
  );
  testLex(
    "obj0123456789",
    { Type::ID }
  );
  testLex(
    "0123456789obj",
    { Type::INT, Type::ID }
  );
  testLex(
    "true1",
    { Type::KW_TRUE, Type::INT }
  );
  testLex("", {});

  testInterpreter({
    MnemonicCode(Mnemonic::POP),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(1)),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(2)),
    MnemonicCode(Mnemonic::ADD)
  }, ValueObject::createIntValue(3));
  
  testInterpreter({
    MnemonicCode(Mnemonic::POP),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(2)),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(1)),
    MnemonicCode(Mnemonic::SUB)
  }, ValueObject::createIntValue(1));

  testInterpreter({
    MnemonicCode(Mnemonic::POP),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(2)),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(1)),
    MnemonicCode(Mnemonic::MUL)
  }, ValueObject::createIntValue(2));

  testInterpreter({
    MnemonicCode(Mnemonic::POP),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(4)),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(2)),
    MnemonicCode(Mnemonic::DIV)
  }, ValueObject::createIntValue(2));

  testInterpreter({
    MnemonicCode(Mnemonic::POP),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(3)),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(2)),
    MnemonicCode(Mnemonic::MOD)
  }, ValueObject::createIntValue(1));

  testInterpreter({
    MnemonicCode(Mnemonic::POP),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(3)),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(2)),
    MnemonicCode(Mnemonic::EQ)
  }, ValueObject::createIntValue(0));

  testInterpreter({
    MnemonicCode(Mnemonic::POP),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(3)),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(3)),
    MnemonicCode(Mnemonic::EQ)
  }, ValueObject::createIntValue(1));

  ValueObject targetValue1;
  testInterpreter({
    MnemonicCode(Mnemonic::POP),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createPointer(&targetValue1)),
    MnemonicCode(Mnemonic::PUSH, ValueObject::createIntValue(3)),
    MnemonicCode(Mnemonic::MOV)
  }, ValueObject::createIntValue(3));
  assert(targetValue1.getIntValue() == 3);

  testParser("3");
  testParser("a");
  testParser("\"Hello, World\"");
  testParser("1.3");

  testInterpreterRun("3", ValueObject::createIntValue(3));

  return 0;
}
