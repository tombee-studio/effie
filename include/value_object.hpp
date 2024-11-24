#pragma once
#include <utils.hpp>
#include <map>
#include <value_type.hpp>
#include <token.hpp>

namespace Effie {
  class ValueObject {
    PROPERTY(ValueType, Type, ValueType::NONE)
    PROPERTY(int, IntValue, 0)
    PROPERTY(double, DoubleValue, 0.0)
    PROPERTY(string, Id, "")

  public:
    static ValueObject createNone() {
      ValueObject value;
      value.setType(ValueType::NONE);
      return value;
    }

    static ValueObject createValueFrom(Token token) {
      ValueObject value;
      switch(token.getType()) {
      case Type::INT:
        value.setType(ValueType::INT);
        value.setIntValue(token.getIntVal());
        break;
      case Type::DOUBLE:
        value.setType(ValueType::DOUBLE);
        value.setDoubleValue(token.getDoubleVal());
        break;
      case Type::ID:
        value.setType(ValueType::STRING);
        value.setId(token.getId());
        break;
      default:
        value.setType(ValueType::NONE);
        break;
      }
      return value;
    }
  };

  typedef map<string, ValueObject> ComponentProperty;
}
