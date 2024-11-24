#include <interpreter.hpp>
using namespace Effie;

void
Interpreter::run() {
  for(auto code: getMnemonics()) {
    runMnemonic(code);
  }
}

void
Interpreter::runMnemonic(MnemonicCode code) {
  switch(code.getOpCode()) {
  case Mnemonic::PUSH:
    getStack().push(code.getValue1());
    break;
  case Mnemonic::POP:
    getStack().pop();
    break;
  default:
    break;
  }
}
