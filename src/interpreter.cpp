#include <interpreter.hpp>
using namespace Effie;

void
Interpreter::run() {
  getStack().push(ValueObject::createNone());
  while(getIsRunning()) {
    runMnemonic(getMnemonics()[getProgramCount()]);
    getProgramCount()++;
  }
}

void
Interpreter::push(MnemonicCode code) {
  getStack().push(code.getValue1());
}

void
Interpreter::pop(MnemonicCode code) {
  getStack().pop();
}

void
Interpreter::add(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.add(value2));
}

void
Interpreter::sub(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.sub(value2));
}

void
Interpreter::mul(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.mul(value2));
}

void
Interpreter::div(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.div(value2));
}

void
Interpreter::mod(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.mod(value2));
}

void
Interpreter::ge(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.ge(value2));
}

void
Interpreter::gt(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.gt(value2));
}

void
Interpreter::le(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.le(value2));
}

void
Interpreter::lt(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.lt(value2));
}

void
Interpreter::eq(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.eq(value2));
}

void
Interpreter::ne(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.ne(value2));
}

void
Interpreter::mov(MnemonicCode code) {
  ValueObject value1;
  ValueObject value2;

  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  if(value1.getType() != ValueType::POINTER) {
    throw runtime_error("need POINTER");
  }
  *(value1.getPointer()) = value2;
  getStack().push(value2);
}

void
Interpreter::nt(MnemonicCode code) {
}

void
Interpreter::get(MnemonicCode code) {
  ValueObject value = getStack().top();
  getStack().pop();
  if(value.getType() != ValueType::POINTER) {
    throw runtime_error("need POINTER");
  }
  getStack().push(*value.getPointer());
}

void
Interpreter::ref(MnemonicCode code) {
  string name = code.getValue1().getId();
  ValueObject value = getStack().top();
  getStack().pop();

  auto& dict = value.getPointer()->getDictionary();
  if(dict.find(name) == dict.end()) {
    dict.insert({ name, ValueObject::createNone() });
  }
  getStack().push(
    ValueObject::createPointer(&dict[name]));
}

void
Interpreter::var(MnemonicCode code) {
  getStack().push(ValueObject::createPointer(&getGlobal()));
}

void
Interpreter::je(MnemonicCode code) {
  ValueObject value = getStack().top();
  getStack().pop();
  int next = code.getValue1().getIntValue();
  if(value.getType() != ValueType::BOOL) {
    throw runtime_error("condition must be boolean");
  }
  if(value.getIntValue() > 0) {
    getProgramCount() = next;
  }
}

void
Interpreter::call(MnemonicCode code) {
  string name = code.getValue1().getId();
  int counts = code.getValue2().getIntValue();
  auto table = getFunctionTable();
  vector<ValueObject> args;
  for(int i = 0; i < counts; i++) {
    ValueObject value = getStack().top();
    args.insert(args.begin(), value);
    getStack().pop();
  }
  getStack().push(table[name](args));
}

void
Interpreter::exit(MnemonicCode code) {
  getIsRunning() = false;
}

void
Interpreter::nop(MnemonicCode code) {
}

void
Interpreter::runMnemonic(MnemonicCode code) {
  switch(code.getOpCode()) {
  case Mnemonic::PUSH:
    push(code);
    break;
  case Mnemonic::POP:
    pop(code);
    break;
  case Mnemonic::ADD:
    add(code);
    break;
  case Mnemonic::SUB:
    sub(code);
    break;
  case Mnemonic::MUL:
    mul(code);
    break;
  case Mnemonic::DIV:
    div(code);
    break;
  case Mnemonic::MOD:
    mod(code);
    break;
  case Mnemonic::GE:
    ge(code);
    break;
  case Mnemonic::GT:
    gt(code);
    break;
  case Mnemonic::LE:
    le(code);
    break;
  case Mnemonic::LT:
    lt(code);
    break;
  case Mnemonic::EQ:
    eq(code);
    break;
  case Mnemonic::NE:
    ne(code);
    break;
  case Mnemonic::MOV:
    mov(code);
    break;
  case Mnemonic::NT:
    nt(code);
    break;
  case Mnemonic::GET:
    get(code);
    break;
  case Mnemonic::REF:
    ref(code);
    break;
  case Mnemonic::VAR:
    var(code);
    break;
  case Mnemonic::JE:
    je(code);
    break;
  case Mnemonic::CALL:
    call(code);
    break;
  case Mnemonic::EXIT:
    exit(code);
    break;
  default:
    nop(code);
    break;
  }
}

ValueObject
Interpreter::getReturnValue() {
  return getStack().top();
}
