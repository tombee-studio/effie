#pragma once
#include <utils.hpp>
#include <value_object.hpp>

namespace Effie {
  enum class CommandType {
    CREATE,
    REMOVE,
    NOP
  };

  class ComponentReference {
    PROPERTY(string, ComponentName, "")
    PROPERTY(string, PropertyName, "")
    PROPERTY(ValueObject, Value, ValueObject::createNone())
  };

  class ComponentObject {
    PROPERTY(string, ComponentName, "")
    PROPERTY(ComponentProperty, Properties, ComponentProperty())

    ComponentObject& operator=(const ComponentObject&) {
      return *this;
    }
  };

  class ICommand {
    PROPERTY(CommandType, Command, CommandType::NOP)

    virtual ~ICommand() {}
  };

  class CreateCommand: public ICommand {
    PROPERTY(ComponentReference, Reference, ComponentReference())
    PROPERTY(vector<ComponentObject>, Components, vector<ComponentObject>())

    virtual ~CreateCommand() override {}
  };

  class RemoveCommand: public ICommand {
    PROPERTY(ComponentReference, Reference, ComponentReference())

    virtual ~RemoveCommand() override {}
  };
};
