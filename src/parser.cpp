#include <parser.hpp>
using namespace Effie;

RootNode* 
Parser::parse() {
  try {
    int index = 0;
    auto root = new RootNode();
    StatementNode *statement;
    while((statement = parseStatement()) != NULL) {
      root->getStatemants().push_back(statement);
    }
    return root;
  } catch(runtime_error& er) {
    cerr << er.what() << endl;
    exit(-1);
  }
}

StatementNode* 
Parser::parseStatement() {
  StatementNode *statement = NULL;
  if((statement = parseExpressionStatement()) != NULL) {
    return statement;
  }
  return NULL;
}

ExpressionStatementNode* 
Parser::parseExpressionStatement() {
  ExpressionNode *node = NULL;
  if((node = parseExpressionNode()) != NULL) {
    return new ExpressionStatementNode(node);
  }
  return NULL;
}

ExpressionNode*
Parser::parseExpressionNode() {
  ExpressionNode *node = NULL;
  if((node = parseMulNode()) != NULL) {
    return node;
  }
}

ExpressionNode *
Parser::parseMulNode() {
  auto node1 = parseTermNode();
  if(node1 == NULL) {
    return NULL;
  }
  if(!(isValidAt(getIndex(), Type::KW_MUL) ||
    isValidAt(getIndex(), Type::KW_DIV))) {
    return node1;
  }
  Token token = consumeNext();
  auto node2 = parseMulNode();
  if(node2 == NULL) {
    throw runtime_error("Unsupported grammar: needs Mul node");
  }
  return new MulExpressionNode(node1, node2, token.getType());
}

ExpressionNode *
Parser::parseTermNode() {
  if(isValidAt(getIndex(), Type::INT) ||
    isValidAt(getIndex(), Type::STRING) ||
    isValidAt(getIndex(), Type::DOUBLE)) {
      Token token = consumeValue();
      return new TermNode(
        ValueObject::createValueFrom(token));
  }

  if(isValidAt(getIndex(), Type::ID)) {
    Token token = consumeValue();
    return new VariableNode(ValueObject::createValueFrom(token));
  }

  if(isValidAt(getIndex(), Type::KW_LPAREN)) {
    consume(Type::KW_LPAREN);
  } else {
    return NULL;
  }

  auto node = parseExpressionNode();
  if(isValidAt(getIndex(), Type::KW_RPAREN)) {
    consume(Type::KW_RPAREN);
  } else {
    throw runtime_error("expected '(' at " + getIndex());
  }
  return node;
}

bool
Parser::isValidAt(int index, Type type) {
  return getTokens()[index].getType() == type;
}

Token
Parser::consume(Type type) {
  auto tokens = getTokens();
  auto index = getIndex();
  if(tokens[index].getType() == type) {
    Token token = tokens[index];
    getIndex()++;
    return token;
  }
  throw runtime_error("");
}

Token
Parser::consumeNext() {
  Token token = getTokens()[getIndex()];
  getIndex()++;
  return token;
}

Token
Parser::consumeValue() {
  auto tokens = getTokens();
  auto index = getIndex();
  if(tokens[index].getType() == Type::ID || 
    tokens[index].getType() == Type::INT ||
    tokens[index].getType() == Type::DOUBLE ||
    tokens[index].getType() == Type::STRING) {
    Token token = tokens[index];
    getIndex()++;
    return token;
  }
  throw runtime_error("");
}
