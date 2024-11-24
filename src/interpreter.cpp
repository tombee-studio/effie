#include <interpreter.hpp>
using namespace Effie;

Interpreter *
Interpreter::instance() {
  static Interpreter *instance = new Interpreter();
  return instance;
}

void
Interpreter::run() {
  auto command = getCommands().top().front();
  runCommand(command);
  delete command;
  getCommands().top().pop();
  if(getCommands().top().size() == 0) {
    getCommands().pop();
  }
}

void
Interpreter::runCommand(ICommand *command) {
  switch(command->getCommand()) {
  case CommandType::CREATE:
    getInterface()->create((Effie::CreateCommand *)command);
    break;
  case CommandType::REMOVE:
    getInterface()->remove((Effie::RemoveCommand *)command);
    break;
  default:
    throw runtime_error("undefined command: " + (int)command->getCommand());
  }
}
