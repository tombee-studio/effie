#pragma once
#include <utils.hpp>
#include <mnemonic_code.hpp>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

namespace Effie {
  class Interpreter {
    PROPERTY(
      vector<MnemonicCode>,
      Mnemonics,
      vector<MnemonicCode>())
    PROPERTY(
      stack<ValueObject>,
      Stack,
      stack<ValueObject>()
    )
    PRIVATE_PROPERTY(
      ValueObject,
      Global,
      ValueObject::createNone()
    )
  public:
    Interpreter() {}

    void run();
    void runMnemonic(MnemonicCode code);
  };
}
