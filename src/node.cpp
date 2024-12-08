#include <node.hpp>
using namespace Effie;

void
AddExpressionNode::compile(vector<MnemonicCode>& codes) {
  getLExp()->compile(codes);
  getRExp()->compile(codes);
  switch(getType()) {
  case Type::KW_ADD:
    codes.push_back(MnemonicCode(Mnemonic::ADD));
    return;
  case Type::KW_SUB:
    codes.push_back(MnemonicCode(Mnemonic::SUB));
    return;
  case Type::KW_MOD:
    codes.push_back(MnemonicCode(Mnemonic::MOD));
    return;
  default:
    throw runtime_error("unsupported operator");
  }
}

void
AddExpressionNode::lcompile(vector<MnemonicCode>& codes) {
  compile(codes);
}

void
MulExpressionNode::compile(vector<MnemonicCode>& codes) {
  getLExp()->compile(codes);
  getRExp()->compile(codes);
  switch(getType()) {
  case Type::KW_MUL:
    codes.push_back(MnemonicCode(Mnemonic::MUL));
    return;
  case Type::KW_DIV:
    codes.push_back(MnemonicCode(Mnemonic::DIV));
    return;
  default:
    throw runtime_error("unsupported operator");
  }
}

void
MulExpressionNode::lcompile(vector<MnemonicCode>& codes) {
  compile(codes);
}

void
TermNode::compile(vector<MnemonicCode>& codes) {
  codes.push_back(MnemonicCode(Mnemonic::PUSH, getValue()));
}

void
TermNode::lcompile(vector<MnemonicCode>& codes) {
  compile(codes);
}

void
VariableNode::compile(vector<MnemonicCode>& codes) {
  codes.push_back(MnemonicCode(Mnemonic::VAR, getName()));
  codes.push_back(MnemonicCode(Mnemonic::REF));
  codes.push_back(MnemonicCode(Mnemonic::GET));
}

void
VariableNode::lcompile(vector<MnemonicCode>& codes) {
  codes.push_back(MnemonicCode(Mnemonic::VAR, getName()));
  codes.push_back(MnemonicCode(Mnemonic::REF));
}

void
ExpressionStatementNode::compile(vector<MnemonicCode>& codes) {
  codes.push_back(MnemonicCode(Mnemonic::POP));
  getExpr()->compile(codes);
}

void
RootNode::compile(vector<MnemonicCode>& codes) {
  codes.push_back(MnemonicCode(Mnemonic::PUSH, ValueObject::createNone()));
  for(auto statement: getStatemants()) {
    statement->compile(codes);
  }
}
