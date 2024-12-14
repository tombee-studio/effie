#pragma once
#include <utils.hpp>
#include <map>
#include <vector>
#include <value_type.hpp>
#include <token.hpp>
#include <icalculatable.hpp>
using namespace std;

namespace Effie {
  class Object: public ICalculatable<Object> {
  public:
    typedef map<string, Object> Dictionary;
    typedef Object (* Function)(vector<Object>);
    typedef map<string, Function> FunctionTable;

    PROPERTY(ValueType, Type, ValueType::DICTIONARY)
    GETTER(int, IntValue, 0)
    GETTER(double, DoubleValue, 0.0)
    GETTER(string, Id, "")
    GETTER(string, StringValue, "")
    GETTER(Dictionary, Dictionary, Dictionary())
    GETTER(Object *, Pointer, NULL);

  public:
    static Object createNone() {
      Object value;
      value.setType(ValueType::DICTIONARY);
      return value;
    }

    static Object createIntValue(int ivalue) {
      Object value;
      value.setIntValue(ivalue);
      value.setType(ValueType::INT);
      return value;
    }

    static Object createBoolValue(bool boolValue) {
      Object value;
      value.setIntValue(boolValue ? 1 : 0);
      value.setType(ValueType::BOOL);
      return value;
    }

    static Object createStringValue(string stringValue) {
      Object value;
      value.setStringValue(stringValue);
      value.setType(ValueType::STRING);
      return value;
    }

    static Object createIdValue(string idValue) {
      Object value;
      value.setId(idValue);
      value.setType(ValueType::ID);
      return value;
    }

    static Object createPointer(Object *pointer) {
      Object value;
      value.setPointer(pointer);
      value.setType(ValueType::POINTER);
      return value;
    }

    static Object createValueFrom(Token token) {
      Object value;
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

    virtual Object add(Object);
    virtual Object sub(Object);
    virtual Object mul(Object);
    virtual Object div(Object);
    virtual Object mod(Object);
    virtual Object eq(Object);
    virtual Object ne(Object);
    virtual Object ge(Object);
    virtual Object gt(Object);
    virtual Object le(Object);
    virtual Object lt(Object);
    // virtual Object nt();
  };
}
