#include <parser.hpp>
using namespace Effie;

RootNode* 
Parser::parse() {
  try {
    int index = 0;
    auto root = new RootNode();
    StatementNode *statement;
    while((statement = parseStatement()) != NULL) {
      if(!isValidAt(getIndex(), Type::KW_SEMICOLON)) {
        throw runtime_error("expected token: ';'");
      }
      consumeNext();
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
  if((node = parseAssignmentNode()) != NULL) {
    return node;
  }
}

ExpressionNode *
Parser::parseAssignmentNode() {
  auto left = parseComparisonNode();
  if(!isValidAt(getIndex(), Type::KW_EQUAL)) {
    return left;
  }
  Token token = consumeNext();
  auto right = parseComparisonNode();
  return new AssignmentExpressionNode(left, right);
}

ExpressionNode *
Parser::parseComparisonNode() {
  auto left = parseAddNode();
  while(isValidAt(getIndex(), Type::KW_EQ) ||
    isValidAt(getIndex(), Type::KW_NE) ||
    isValidAt(getIndex(), Type::KW_GE) ||
    isValidAt(getIndex(), Type::KW_GT) ||
    isValidAt(getIndex(), Type::KW_LE) ||
    isValidAt(getIndex(), Type::KW_LT)) {
    Token token = consumeNext();
    auto right = parseAddNode();
    left = new ComparisonExpressionNode(left, right, token.getType());
  }
  return left;
}

ExpressionNode *
Parser::parseAddNode() {
  auto left = parseMulNode();
  while(isValidAt(getIndex(), Type::KW_ADD) ||
    isValidAt(getIndex(), Type::KW_SUB)) {
    Token token = consumeNext();
    auto right = parseMulNode();
    left = new AddExpressionNode(left, right, token.getType());
  }
  return left;
}

ExpressionNode *
Parser::parseMulNode() {
  auto left = parseTermNode();
  while(isValidAt(getIndex(), Type::KW_MUL) ||
    isValidAt(getIndex(), Type::KW_DIV) ||
    isValidAt(getIndex(), Type::KW_MOD)) {
    Token token = consumeNext();
    auto right = parseTermNode();
    left = new MulExpressionNode(left, right, token.getType());
  }
  return left;
}

ArgumentNode *
Parser::parseArgumentNode() {
  vector<ExpressionNode *> arguments;
  if(!isValidAt(getIndex(), Type::KW_LPAREN)) {
    return NULL;
  }
  consumeNext();
  while(true) {
    arguments.push_back(parseExpressionNode());
    if(isValidAt(getIndex(), Type::KW_COMMA)) {
      consumeNext();
      continue;
    }
    if(isValidAt(getIndex(), Type::KW_RPAREN)) {
      consumeNext();
      break;
    }
  }
  return new ArgumentNode(arguments);
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
    Token token = consumeNext();
    auto argument = parseArgumentNode();
    if(argument == NULL) {
      return new VariableNode(ValueObject::createValueFrom(token));
    } else {
      return new CallFunctionNode(token.getId(), argument);
    }
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
