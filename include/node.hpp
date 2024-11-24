#pragma once
#include <utils.hpp>
#include <lexer.hpp>
#include <command.hpp>
#include <value_object.hpp>
#include <command.hpp>
#include <vector>
#include <map>
#include <queue>
using namespace std;

namespace Effie {
  class Node {
    PROPERTY(Type, Type, Type::NONE)
  };

  class StatementNode: public Node {
  public:
    virtual ~StatementNode() {}
  };

  class AssignmentStatementNode: public StatementNode {
  public:
    virtual ~AssignmentStatementNode() override {}
  };

  class ExpressionNode: public Node {
  public:
    virtual ~ExpressionNode() {}
  };

  class RootNode: public Node {
    PROPERTY(vector<StatementNode *>,
      Statemants,
      vector<StatementNode *>())

    ~RootNode() {
      for(auto node: _Statemants) {
        delete node;
      }
    }
  };
}
