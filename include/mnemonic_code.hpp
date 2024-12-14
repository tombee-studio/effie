#pragma once

#include <mnemonic.hpp>
#include <value_object.hpp>
#include <utils.hpp>

namespace Effie {
  class MnemonicCode {
    GETTER(Mnemonic, OpCode, Mnemonic::NOP)
    GETTER(Object, Value1, Object::createNone())
    GETTER(Object, Value2, Object::createNone())
  public:
    MnemonicCode() {

    }
  
    MnemonicCode(Mnemonic opCode) {
      setOpCode(opCode);
    }

    MnemonicCode(Mnemonic opCode, Object value1) {
      setOpCode(opCode);
      setValue1(value1);
    }

    MnemonicCode(Mnemonic opCode, Object value1, Object value2) {
      setOpCode(opCode);
      setValue1(value1);
      setValue2(value2);
    }
  };
}
