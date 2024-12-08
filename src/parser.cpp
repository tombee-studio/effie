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
  if((node = parseTermNode()) != NULL) {
    return node;
  }
}

ExpressionNode *
Parser::parseTermNode() {
  if(isValidAt(getIndex(), Type::ID) || 
    isValidAt(getIndex(), Type::INT) ||
    isValidAt(getIndex(), Type::STRING) ||
    isValidAt(getIndex(), Type::DOUBLE)) {
      Token token = consumeValue();
      return new TermNode(
        ValueObject::createValueFrom(token));
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
