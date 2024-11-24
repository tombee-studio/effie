#include <parser.hpp>
using namespace Effie;

Token Parser::none = Token::createNone();

RootNode* 
Parser::parse(vector<Token>& tokens) {
  try {
    int index = 0;
    auto root = new RootNode();
    StatementNode *statement;
    while((statement = parseStatement(tokens, index)) != NULL) {
      root->getStatemants().push_back(statement);
    }
    return root;
  } catch(runtime_error& er) {
    cerr << er.what() << endl;
    exit(-1);
  }
}

StatementNode* 
Parser::parseStatement(vector<Token>& tokens, int& index) {
  Token token;
  return NULL;
}

bool
Parser::consume(Token& target, vector<Token>& tokens, int& index, Type type) {
  if(tokens[index].getType() == type) {
    target = tokens[index];
    index++;
    return true;
  }
  target = none;
  return false;
}

bool
Parser::consumeValue(Token& target, vector<Token>& tokens, int& index) {
  if(tokens[index].getType() == Type::ID || 
    tokens[index].getType() == Type::INT ||
    tokens[index].getType() == Type::DOUBLE) {
    target = tokens[index];
    index++;
    return true;
  }
  target = none;
  return false;
}
