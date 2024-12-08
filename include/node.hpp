#pragma once
#include <utils.hpp>
#include <lexer.hpp>
#include <value_object.hpp>
#include <mnemonic_code.hpp>
#include <vector>
#include <map>
#include <queue>
using namespace std;

namespace Effie {
  class Node {
  public:
    virtual void compile(vector<MnemonicCode>&) {}
  };

    class ExpressionNode: public Node {
  public:
    virtual ~ExpressionNode() {}

    virtual void compile(vector<MnemonicCode>&) override {}
  };

  class BinaryExpressionNode: public ExpressionNode {
  protected:
    GETTER(ExpressionNode *, LExp, NULL)
    GETTER(ExpressionNode *, RExp, NULL)
  public:
    BinaryExpressionNode(ExpressionNode *lexp, ExpressionNode *rexp) {
      setLExp(lexp);
      setRExp(rexp);
    }

    ~BinaryExpressionNode() override {
      delete _LExp;
      delete _RExp;
    }

    void compile(vector<MnemonicCode>& codes) override;
  };

  class MulExpressionNode: public BinaryExpressionNode {
  public:
    MulExpressionNode(ExpressionNode *lexp, ExpressionNode *rexp): 
      BinaryExpressionNode(lexp, rexp) {}

    ~MulExpressionNode() override {
      BinaryExpressionNode::~BinaryExpressionNode();
    }

    void compile(vector<MnemonicCode>& codes) override;
  };

  class TermNode: public ExpressionNode {
    PRIVATE_PROPERTY(ValueObject, Value, ValueObject::createNone())
  public:
    TermNode(ValueObject value) {
      setValue(value);
    }

    ~TermNode() override {

    }

    void compile(vector<MnemonicCode>& codes) override;
  };

  class StatementNode: public Node {
  public:
    virtual ~StatementNode() {}

    virtual void compile(vector<MnemonicCode>& codes) override {}
  };

  class ExpressionStatementNode: public StatementNode {
    PRIVATE_PROPERTY(ExpressionNode *, Expr, NULL);
  public:
    ExpressionStatementNode(ExpressionNode *node): _Expr(node) {}

    virtual ~ExpressionStatementNode() override {
      delete _Expr;
    }

    void compile(vector<MnemonicCode>& codes) override;
  };

  class RootNode: public Node {
    GETTER(vector<StatementNode *>,
      Statemants,
      vector<StatementNode *>())
  public:
    ~RootNode() {
      for(auto node: _Statemants) {
        delete node;
      }
    }

    void compile(vector<MnemonicCode>&) override;
  };
}
