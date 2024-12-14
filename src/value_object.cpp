#include <value_object.hpp>
using namespace Effie;

Object
Object::add(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }
  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() + value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object
Object::sub(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() - value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object
Object::mul(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() * value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object 
Object::div(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() / value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object 
Object::mod(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() % value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object 
Object::eq(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() == value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object
Object::ne(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() != value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object
Object::ge(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() >= value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object
Object::gt(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() > value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object
Object::le(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() <= value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

Object
Object::lt(Object value) {
  if(getType() != value.getType()) {
    throw runtime_error("型の不一致");
  }

  switch(getType()) {
  case ValueType::INT:
    return Object::createIntValue(getIntValue() < value.getIntValue());
  default:
    throw runtime_error("Unsupported operation");
  }
}

// Object
// Object::nt() {
//   switch(getType()) {
//   case ValueType::INT:
//     return Object::createIntValue(!getIntValue());
//   default:
//     throw runtime_error("Unsupported operation");
//   }
// }
