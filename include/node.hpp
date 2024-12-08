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

    virtual void compile(vector<MnemonicCode>&) = 0;
    virtual void lcompile(vector<MnemonicCode>& codes) = 0;
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
  };

  class TermNode: public ExpressionNode {
    PRIVATE_PROPERTY(ValueObject, Value, ValueObject::createNone())
  public:
    TermNode(ValueObject value) {
      setValue(value);
    }

    ~TermNode() override {

    }

    virtual void compile(vector<MnemonicCode>& codes) override;
    virtual void lcompile(vector<MnemonicCode>& codes) override;
  };

  class VariableNode: public ExpressionNode {
    PRIVATE_PROPERTY(ValueObject, Name, ValueObject::createNone())
  public:
    VariableNode(ValueObject name) {
      setName(name);
    }

    ~VariableNode() override {}

    virtual void compile(vector<MnemonicCode>& codes) override;
    virtual void lcompile(vector<MnemonicCode>& codes) override;
  };

  class StatementNode: public Node {
  public:
    virtual ~StatementNode() {}

    virtual void compile(vector<MnemonicCode>& codes) = 0;
  };

  class ExpressionStatementNode: public StatementNode {
    PRIVATE_PROPERTY(ExpressionNode *, Expr, NULL);
  public:
    ExpressionStatementNode(ExpressionNode *node): _Expr(node) {}

    virtual ~ExpressionStatementNode() override {
      delete _Expr;
    }

    virtual void compile(vector<MnemonicCode>& codes) override;
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

    virtual void compile(vector<MnemonicCode>&) override;
  };
}
