#include <interpreter.hpp>
using namespace Effie;

void
Interpreter::run() {
  getStack().push(ValueObject::createNone());
  for(auto code: getMnemonics()) {
    runMnemonic(code);
  }
}

void
Interpreter::runMnemonic(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  switch(code.getOpCode()) {
  case Mnemonic::PUSH:
    getStack().push(code.getValue1());
    break;
  case Mnemonic::POP:
    getStack().pop();
    break;
  case Mnemonic::ADD:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.add(value2));
    break;
  case Mnemonic::SUB:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.sub(value2));
    break;
  case Mnemonic::MUL:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.mul(value2));
    break;
  case Mnemonic::DIV:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.div(value2));
    break;
  case Mnemonic::MOD:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.mod(value2));
    break;
  case Mnemonic::GE:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.ge(value2));
    break;
  case Mnemonic::GT:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.gt(value2));
    break;
  case Mnemonic::LE:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.le(value2));
    break;
  case Mnemonic::LT:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.lt(value2));
    break;
  case Mnemonic::EQ:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.eq(value2));
    break;
  case Mnemonic::NE:
    value2 = getStack().top();
    getStack().pop();
    value1 = getStack().top();
    getStack().pop();
    getStack().push(value1.ne(value2));
    break;
  // case Mnemonic::NT:
  //   value1 = getStack().top();
  //   getStack().pop();
  //   getStack().push(value1.nt());
  //   break;
  default:
    break;
  }
}
