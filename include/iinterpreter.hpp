#pragma once
#include <mnemonic_code.hpp>

namespace Effie {
  class IInterpreter {
  protected:
    virtual void push(MnemonicCode code) = 0;
    virtual void pop(MnemonicCode code) = 0;
    virtual void mov(MnemonicCode code) = 0;
    virtual void add(MnemonicCode code) = 0;
    virtual void sub(MnemonicCode code) = 0;
    virtual void mul(MnemonicCode code) = 0;
    virtual void div(MnemonicCode code) = 0;
    virtual void mod(MnemonicCode code) = 0;
    virtual void ge(MnemonicCode code) = 0;
    virtual void gt(MnemonicCode code) = 0;
    virtual void le(MnemonicCode code) = 0;
    virtual void lt(MnemonicCode code) = 0;
    virtual void eq(MnemonicCode code) = 0;
    virtual void ne(MnemonicCode code) = 0;
    virtual void nt(MnemonicCode code) = 0;
    virtual void get(MnemonicCode code) = 0;
    virtual void ref(MnemonicCode code) = 0;
    virtual void var(MnemonicCode code) = 0;
    virtual void je(MnemonicCode code) = 0;
    virtual void jne(MnemonicCode code) = 0;
    virtual void jmp(MnemonicCode code) = 0;
    virtual void call(MnemonicCode code) = 0;
    virtual void exit(MnemonicCode code) = 0;
    virtual void nop(MnemonicCode code) = 0;
  };
}