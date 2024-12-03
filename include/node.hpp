#pragma once
#include <utils.hpp>
#include <lexer.hpp>
#include <value_object.hpp>
#include <vector>
#include <map>
#include <queue>
using namespace std;

namespace Effie {
  class Node {
  public:
    
  };

  class StatementNode: public Node {
  public:
    virtual ~StatementNode() {}
  };

  class ExpressionStatementNode: public StatementNode {
  public:
    virtual ~ExpressionStatementNode() override;
  };

  class ExpressionNode: public Node {
  public:
    virtual ~ExpressionNode() {}
  };

  class BinaryExpressionNode: public ExpressionNode {
  protected:
    PRIVATE_PROPERTY(ExpressionNode *, LExp, NULL)
    PRIVATE_PROPERTY(ExpressionNode *, RExp, NULL)
  public:
    BinaryExpressionNode(ExpressionNode *lexp, ExpressionNode *rexp) {
      setLExp(lexp);
      setRExp(rexp);
    }

    ~BinaryExpressionNode() override {
      delete _LExp;
      delete _RExp;
    }
  };

  class RootNode: public Node {
    GETTER(vector<StatementNode *>,
      Statemants,
      vector<StatementNode *>())

    ~RootNode() {
      for(auto node: _Statemants) {
        delete node;
      }
    }
  };
}
