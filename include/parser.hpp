#pragma once
#include <node.hpp>

namespace Effie {
  class Parser {
    static Token none;
  public:
    static RootNode* parse(vector<Token>&);
  private:
    static bool consume(Token&, vector<Token>&, int&, Type);
    static bool consumeValue(Token&, vector<Token>&, int&);

    static RootNode* parseRoot(vector<Token>&, int&);
    static StatementNode* parseStatement(vector<Token>&, int&);
    static ExpressionStatementNode * parseExpressionStatement(vector<Token>&, int&);
  };
}
