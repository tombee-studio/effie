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

  class TermNode: public ExpressionNode {
    PRIVATE_PROPERTY(ValueObject, Value, ValueObject::createNone())
  public:
    TermNode(ValueObject value) {
      setValue(value);
    }

    ~TermNode() override {

    }
  };

  class StatementNode: public Node {
  public:
    virtual ~StatementNode() {}
  };

  class ExpressionStatementNode: public StatementNode {
    PRIVATE_PROPERTY(ExpressionNode *, Expr, NULL);
  public:
    ExpressionStatementNode(ExpressionNode *node): _Expr(node) {}

    virtual ~ExpressionStatementNode() override {
      delete _Expr;
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
