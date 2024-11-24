#pragma once
#include <utils.hpp>
#include <map>
#include <value_type.hpp>
#include <token.hpp>
using namespace std;

namespace Effie {
  class ValueObject {
    typedef map<string, ValueObject> Dictionary;

    PROPERTY(ValueType, Type, ValueType::DICTIONARY)
    PROPERTY(int, IntValue, 0)
    PROPERTY(double, DoubleValue, 0.0)
    PROPERTY(string, Id, "")
    PROPERTY(Dictionary, Dictionary, Dictionary())
    PROPERTY(ValueObject *, Pointer, NULL);

  public:
    static ValueObject createNone() {
      ValueObject value;
      value.setType(ValueType::DICTIONARY);
      return value;
    }

    static ValueObject createPointer(ValueObject *pointer) {
      ValueObject value;
      value.setPointer(pointer);
      value.setType(ValueType::POINTER);
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
        value.setType(ValueType::DICTIONARY);
        break;
      }
      return value;
    }
  };
}
