#pragma once
#include <utils.hpp>
#include <stack>
#include <queue>
#include <command.hpp>
#include <iinterpreter.hpp>
using namespace std;

namespace Effie {
  class Interpreter {
    PROPERTY(
      stack<queue<ICommand *>>,
      Commands,
      stack<queue<ICommand *>>());
    PROPERTY(IInterpreter *, Interface, NULL);
  private:
    Interpreter() {}
  public:
    static Interpreter *instance();

    void run();
  private:
    void runCommand(ICommand *command);
  };
}
