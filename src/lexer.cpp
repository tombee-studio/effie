#include <lexer.hpp>
using namespace Effie;

vector<Token> 
Lexer::lex(string text) {
  vector<Token> tokens;
  const char *cText = text.data();
  int index = 0;
  Token token;
  while(true) {
    if(index >= text.size()) {
      return tokens;
    }
    if(skipSpace(cText, index)) continue;
    if(lexKW(tokens, cText, index, "==", Type::KW_EQ)) continue;
    if(lexKW(tokens, cText, index, "true", Type::KW_TRUE)) continue;
    if(lexKW(tokens, cText, index, "false", Type::KW_FALSE)) continue;
    if(lexKW(tokens, cText, index, "!=", Type::KW_NE)) continue;
    if(lexKW(tokens, cText, index, ">=", Type::KW_GE)) continue;
    if(lexKW(tokens, cText, index, "<=", Type::KW_LE)) continue;
    if(lexKW(tokens, cText, index, ":", Type::KW_COLON)) continue;
    if(lexKW(tokens, cText, index, ";", Type::KW_SEMICOLON)) continue;
    if(lexKW(tokens, cText, index, "=", Type::KW_EQUAL)) continue;
    if(lexKW(tokens, cText, index, ".", Type::KW_DOT)) continue;
    if(lexKW(tokens, cText, index, ",", Type::KW_COMMA)) continue;
    if(lexKW(tokens, cText, index, "[", Type::KW_LBRACKET)) continue;
    if(lexKW(tokens, cText, index, "]", Type::KW_RBRACKET)) continue;
    if(lexKW(tokens, cText, index, "*", Type::KW_MUL)) continue;
    if(lexKW(tokens, cText, index, "/", Type::KW_DIV)) continue;
    if(lexKW(tokens, cText, index, "%", Type::KW_MOD)) continue;
    if(lexKW(tokens, cText, index, "+", Type::KW_ADD)) continue;
    if(lexKW(tokens, cText, index, "-", Type::KW_SUB)) continue;
    if(lexKW(tokens, cText, index, "(", Type::KW_LPAREN)) continue;
    if(lexKW(tokens, cText, index, ")", Type::KW_RPAREN)) continue;
    if(lexKW(tokens, cText, index, ">", Type::KW_GT)) continue;
    if(lexKW(tokens, cText, index, "<", Type::KW_LT)) continue;
    if(lexKW(tokens, cText, index, "!", Type::KW_NOT)) continue;
    if(lexString(tokens, cText, index)) continue;
    if(lexDouble(tokens, cText, index)) continue;
    if(lexInt(tokens, cText, index)) continue;
    if(lexId(tokens, cText, index)) continue;
    cerr << "can't lex word found: " << cText[index] << "@" << index << endl;
    exit(-1);
  }
}

bool
Lexer::skipSpace(const char *text, int& index) {
  if(text[index] == ' ' || 
    text[index] == '\t' || 
    text[index] == '\n' || 
    text[index] == '\r') {
    index++;
    return true;
  }
  return false;
}

bool
Lexer::lexKW(vector<Token>& tokens, const char *text, int& index, string keyword, Type type) {
  if(strncmp(&(text[index]), keyword.data(), keyword.size()) == 0) {
    tokens.push_back(Token::createKeywordToken(type));
    index += keyword.size();
    return true;
  }
  return false;
}

bool
Lexer::lexString(vector<Token>& tokens, const char *text, int& index) {
  if(text[index] != '\"') {
    return false;
  }
  
  int start = index;
  int size = 1;
  while(text[start + size] != '\"') {
    size++;
  }
  size += 1;

  char str[size - 1];
  strncpy(str, &(text[index + 1]), size - 2);
  str[size - 1] = 0;

  tokens.push_back(Token::createStringToken(str));
  index = start + size;
  return true;
}

bool
Lexer::lexInt(vector<Token>& tokens, const char *text, int& index) {
  if(text[index] < '0' || '9' < text[index]) {
    return false;
  }
  
  int start = index;
  int size = 1;
  while('0' <= text[start + size] && text[start + size] <= '9') {
    size++;
  }

  char str[size + 1];
  strncpy(str, &(text[index]), size);

  int value = atoi(str);
  tokens.push_back(Token::createIntToken(value));
  index = start + size;
  return true;
}

bool
Lexer::lexDouble(vector<Token>& tokens, const char *text, int& index) {
  if(text[index] < '0' || '9' < text[index]) {
    return false;
  }
  
  bool hasDot = false;
  int start = index;
  int size = 1;
  while(('0' <= text[start + size] && text[start + size] <= '9') ||
    text[start + size] == '.') {
      if(text[start + size] == '.') {
        hasDot = true;
      }
      size++;
  }

  if(!hasDot) {
    return false;
  }

  char str[size + 1];
  strncpy(str, &(text[index]), size);

  double value = stod(str);
  tokens.push_back(Token::createDoubleToken(value));
  index = start + size;
  return true;
}

bool
Lexer::lexId(vector<Token>& tokens, const char *text, int& index) {
  if(!isIdentifier(text[index])) {
    return false;
  }
  
  int start = index;
  int size = 1;
  while(isIdentifier(text[start + size]) || isNumber(text[start + size])) {
    size++;
  }

  char str[size + 1];
  str[size] = 0;
  strncpy(str, &(text[index]), size);
  tokens.push_back(Token::createIdToken(string(str)));
  index = start + size;
  return true;
}

bool
Lexer::isIdentifier(char c) {
  return ('A' <= c && c <= 'Z') 
    || ('a' <= c && c <= 'z')
    || c == '_';
}

bool
Lexer::isNumber(char c) {
  return '0' <= c && c <= '9';
}
