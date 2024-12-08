#include <node.hpp>
using namespace Effie;

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
