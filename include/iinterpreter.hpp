#pragma once

#include <command.hpp>

namespace Effie {
  class IInterpreter {
  public:
    virtual void create(CreateCommand *) = 0;
    virtual void remove(RemoveCommand *) = 0;
  };
}
