#include <value_object.hpp>
using namespace Effie;

ValueObject
ValueObject::add(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }
  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() + value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject
ValueObject::sub(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() - value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject
ValueObject::mul(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() * value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject 
ValueObject::div(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() / value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject 
ValueObject::mod(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() % value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject 
ValueObject::eq(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() == value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject
ValueObject::ne(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() != value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject
ValueObject::ge(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() >= value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject
ValueObject::gt(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() > value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject
ValueObject::le(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() <= value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject
ValueObject::lt(ValueObject value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(getIntValue() < value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

ValueObject
ValueObject::nt() {
  switch(getType()) {
  case ValueType::INT:
    return ValueObject::createIntValue(!getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}
