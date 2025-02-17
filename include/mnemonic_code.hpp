#pragma once

#include <mnemonic.hpp>
#include <value_object.hpp>
#include <utils.hpp>

namespace Effie {
  class MnemonicCode {
    PROPERTY(Mnemonic, OpCode, Mnemonic::NOP)
    PROPERTY(ValueObject, Value1, ValueObject::createNone())
    PROPERTY(ValueObject, Value2, ValueObject::createNone())
  public:
    MnemonicCode(Mnemonic opCode) {
      setOpCode(opCode);
    }

    MnemonicCode(Mnemonic opCode, ValueObject value1) {
      setOpCode(opCode);
      setValue1(value1);
    }

    MnemonicCode(Mnemonic opCode, ValueObject value1, ValueObject value2) {
      setOpCode(opCode);
      setValue1(value1);
      setValue2(value2);
    }
  };
}
