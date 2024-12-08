#pragma once
#include <utils.hpp>
#include <map>
#include <value_type.hpp>
#include <token.hpp>
#include <icalculatable.hpp>
using namespace std;

namespace Effie {
  class ValueObject: public ICalculatable<ValueObject> {
    typedef map<string, ValueObject> Dictionary;

    PROPERTY(ValueType, Type, ValueType::DICTIONARY)
    GETTER(int, IntValue, 0)
    GETTER(double, DoubleValue, 0.0)
    GETTER(string, Id, "")
    GETTER(string, StringValue, "")
    GETTER(Dictionary, Dictionary, Dictionary())
    GETTER(ValueObject *, Pointer, NULL);

  public:
    static ValueObject createNone() {
      ValueObject value;
      value.setType(ValueType::DICTIONARY);
      return value;
    }

    static ValueObject createIntValue(int ivalue) {
      ValueObject value;
      value.setIntValue(ivalue);
      value.setType(ValueType::INT);
      return value;
    }

    static ValueObject createBoolValue(bool boolValue) {
      ValueObject value;
      value.setIntValue(boolValue ? 1 : 0);
      value.setType(ValueType::BOOL);
      return value;
    }

    static ValueObject createStringValue(string stringValue) {
      ValueObject value;
      value.setStringValue(stringValue);
      value.setType(ValueType::STRING);
      return value;
    }

    static ValueObject createIdValue(string idValue) {
      ValueObject value;
      value.setId(idValue);
      value.setType(ValueType::ID);
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
        value.setType(ValueType::ID);
        value.setId(token.getId());
        break;
      case Type::STRING:
        value.setType(ValueType::STRING);
        value.setStringValue(token.getStringVal());
        break;
      case Type::KW_TRUE:
        value.setType(ValueType::BOOL);
        value.setIntValue(1);
        break;
      case Type::KW_FALSE:
        value.setType(ValueType::BOOL);
        value.setIntValue(0);
        break;
      default:
        value.setType(ValueType::DICTIONARY);
        break;
      }
      return value;
    }

    virtual ValueObject add(ValueObject);
    virtual ValueObject sub(ValueObject);
    virtual ValueObject mul(ValueObject);
    virtual ValueObject div(ValueObject);
    virtual ValueObject mod(ValueObject);
    virtual ValueObject eq(ValueObject);
    virtual ValueObject ne(ValueObject);
    virtual ValueObject ge(ValueObject);
    virtual ValueObject gt(ValueObject);
    virtual ValueObject le(ValueObject);
    virtual ValueObject lt(ValueObject);
    // virtual ValueObject nt();
  };
}
