#include <interpreter.hpp>
using namespace Effie;

void
Interpreter::run() {
  getStack().push(Object::createNone());
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
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.add(value2));
}

void
Interpreter::sub(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.sub(value2));
}

void
Interpreter::mul(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.mul(value2));
}

void
Interpreter::div(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.div(value2));
}

void
Interpreter::mod(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.mod(value2));
}

void
Interpreter::ge(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.ge(value2));
}

void
Interpreter::gt(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.gt(value2));
}

void
Interpreter::le(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.le(value2));
}

void
Interpreter::lt(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.lt(value2));
}

void
Interpreter::eq(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.eq(value2));
}

void
Interpreter::ne(MnemonicCode code) {
  Object value1;
  Object value2;
  value2 = getStack().top();
  getStack().pop();
  value1 = getStack().top();
  getStack().pop();
  getStack().push(value1.ne(value2));
}

void
Interpreter::mov(MnemonicCode code) {
  Object value1;
  Object value2;

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
  Object value = getStack().top();
  getStack().pop();
  if(value.getType() != ValueType::POINTER) {
    throw runtime_error("need POINTER");
  }
  getStack().push(*value.getPointer());
}

void
Interpreter::ref(MnemonicCode code) {
  string name = code.getValue1().getId();
  Object value = getStack().top();
  getStack().pop();

  auto& dict = value.getPointer()->getDictionary();
  if(dict.find(name) == dict.end()) {
    dict.insert({ name, Object::createNone() });
  }
  getStack().push(
    Object::createPointer(&dict[name]));
}

void
Interpreter::var(MnemonicCode code) {
  getStack().push(Object::createPointer(&getGlobal()));
}

void
Interpreter::je(MnemonicCode code) {
  Object value = getStack().top();
  int next = code.getValue1().getIntValue();
  if(value.getIntValue() > 0) {
    getProgramCount() = next - 1;
  }
}

void
Interpreter::jmp(MnemonicCode code) {
  int next = code.getValue1().getIntValue();
  getProgramCount() = next - 1;
}

void
Interpreter::jne(MnemonicCode code) {
  Object value = getStack().top();
  int next = code.getValue1().getIntValue();
  if(value.getIntValue() == 0) {
    getProgramCount() = next - 1;
  }
}

void
Interpreter::call(MnemonicCode code) {
  string name = code.getValue1().getId();
  int counts = code.getValue2().getIntValue();
  auto table = getFunctionTable();
  vector<Object> args;
  for(int i = 0; i < counts; i++) {
    Object value = getStack().top();
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
  case Mnemonic::JNE:
    jne(code);
    break;
  case Mnemonic::JMP:
    jmp(code);
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

Object
Interpreter::getReturnValue() {
  return getStack().top();
}
