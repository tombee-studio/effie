#pragma once
#include <value_object.hpp>
#include <utils.hpp>
#include <iinterpreter.hpp>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using namespace std;

namespace Emile {
  class Interpreter: public IInterpreter {
    PROPERTY(
      vector<MnemonicCode>,
      Mnemonics,
      vector<MnemonicCode>())
    PROPERTY(
      stack<Object>,
      Stack,
      stack<Object>()
    )
    PRIVATE_PROPERTY(
      Object,
      Global,
      Object::createNone()
    )
    PRIVATE_PROPERTY(
      bool,
      IsRunning,
      true
    )
    PRIVATE_PROPERTY(
      int,
      ProgramCount,
      0
    )
    GETTER(
      Object::FunctionTable,
      FunctionTable,
      Object::FunctionTable()
    )
  public:
    Interpreter() {}

    void run();
    void runMnemonic(MnemonicCode code);

    Object getReturnValue();

  protected:
    virtual void push(MnemonicCode code);
    virtual void pop(MnemonicCode code);
    virtual void mov(MnemonicCode code);
    virtual void add(MnemonicCode code);
    virtual void sub(MnemonicCode code);
    virtual void mul(MnemonicCode code);
    virtual void div(MnemonicCode code);
    virtual void mod(MnemonicCode code);
    virtual void ge(MnemonicCode code);
    virtual void gt(MnemonicCode code);
    virtual void le(MnemonicCode code);
    virtual void lt(MnemonicCode code);
    virtual void eq(MnemonicCode code);
    virtual void ne(MnemonicCode code);
    virtual void nt(MnemonicCode code);
    virtual void get(MnemonicCode code);
    virtual void ref(MnemonicCode code);
    virtual void var(MnemonicCode code);
    virtual void je(MnemonicCode code);
    virtual void jne(MnemonicCode code);
    virtual void jmp(MnemonicCode code);
    virtual void call(MnemonicCode code);
    virtual void exit(MnemonicCode code);
    virtual void nop(MnemonicCode code);
  };
}
