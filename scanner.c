#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKENS 1000
#define TOKEN_LENGTH 20
#define TOTAL_WORDS 8
#define TOTAL_SYMBOLS 11

char *words[] = {"if", "then", "else", "end", "repeat", "until", "read", "write"};
char *symbols[] = {"+", "-", "*", "/", ";", "=", "<", ">", "(", ")", ":="};

typedef enum {
  WORD, IDENTIFIER, NUM, STR, SYMBOL, UNKNOWN, LENGTH_ERROR
} TokenType;

typedef struct {
  TokenType type;
  char *data;
  int line;
} Token;

int isEqual(const char* str1, const char* str2);
char* assign(char* dest, const char* src);
const char* getTokenType(TokenType type);
size_t getLength(const char* str);
void reset(void* ptr);
int isIdentifier(char *token);
int isSymbol(char *token);
int isNumber(char *token);
int isWord(char *token);

int main() {
  char fdata;

  Token token;
  token.data = malloc(sizeof(char) * TOKEN_LENGTH);
  token.line = 0;

  int tokens_quantity = 0;
  Token *tokens = malloc(sizeof(Token) * MAX_TOKENS);

  int raw_token_idx = 0;
  char raw_token[TOKEN_LENGTH];

  int line_counter = 1;

  while ((fdata = getchar()) != EOF) {
    raw_token[raw_token_idx] = fdata;

    if(fdata == '\n') {
      raw_token[raw_token_idx] = '\0';
      
      if(isWord(raw_token)) {
        token.data = malloc(sizeof(char) * (raw_token_idx + 1));
        token.type = WORD;
        token.line = line_counter;
        assign(token.data, raw_token);
        tokens[tokens_quantity++] = token;
      }
      else if(isIdentifier(raw_token)) {
        token.data = malloc(sizeof(char) * (raw_token_idx + 1));
        token.type = IDENTIFIER;
        token.line = line_counter;
        assign(token.data, raw_token);
        tokens[tokens_quantity++] = token;
      }

      line_counter++;

      raw_token_idx = 0;
      reset(raw_token);
    }
    else if(fdata == '{') {
      while ((fdata = getchar()) != '}') {
        continue;
      }
    } 
    else if(fdata == '"') {
      int string_counter = 0;
      int length_error = 0;

      while ((fdata = getchar()) != '"') {
        raw_token[raw_token_idx++] = fdata;
        string_counter++;

        if(string_counter > TOKEN_LENGTH) {
          length_error = 1;
          break;
        }
      }
      raw_token[raw_token_idx] = '\0';
      
      while ((fdata = getchar()) != '\n') {
        continue;
      }
      line_counter ++;

      if(length_error) {
        token.type = LENGTH_ERROR;
      } else {
        token.type = STR;
      }

      token.data = malloc(sizeof(char) * (raw_token_idx + 1));
      token.line = line_counter;
      assign(token.data, raw_token);
      tokens[tokens_quantity++] = token;

      raw_token_idx = 0;
      reset(raw_token);
    }
    else if(isSymbol(raw_token) || fdata == ':') {
      if(raw_token_idx > 0) {
        raw_token[raw_token_idx] = '\0';
        
        if(isWord(raw_token)) {
          token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
          token.type = WORD;
          assign(token.data, raw_token);
          tokens[tokens_quantity++] = token;
        }
        else if(isIdentifier(raw_token)) {
          token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
          token.type = IDENTIFIER;
          assign(token.data, raw_token);
          tokens[tokens_quantity++] = token;
        }
        else if (isNumber(raw_token)) {
          token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
          token.type = NUM;
          assign(token.data, raw_token);
          tokens[tokens_quantity++] = token;
        }

        raw_token_idx = 0;
        reset(raw_token); 
      }
      
      raw_token[raw_token_idx++] = fdata;

      if(fdata == ':') {
        if((fdata = getchar()) == '=') {
          raw_token[raw_token_idx++] = fdata;
        }
      }

      if(isSymbol(raw_token)) {
        token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
        token.type = SYMBOL;
        assign(token.data, raw_token);
        tokens[tokens_quantity++] = token;
      }

      raw_token_idx = 0;
      reset(raw_token); 
    }
    else if(fdata == '(' || fdata == ')') {
      if(raw_token_idx > 0) {
        raw_token[raw_token_idx] = '\0';
        
        if(isWord(raw_token)) {
          token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
          token.type = WORD;
          assign(token.data, raw_token);
          tokens[tokens_quantity++] = token;
        }
        else if(isIdentifier(raw_token)) {
          token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
          token.type = IDENTIFIER;
          assign(token.data, raw_token);
          tokens[tokens_quantity++] = token;
        }
        else if (isNumber(raw_token)) {
          token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
          token.type = NUM;
          assign(token.data, raw_token);
          tokens[tokens_quantity++] = token;
        }

        raw_token_idx = 0;
        reset(raw_token); 
      }
      
      raw_token[raw_token_idx++] = fdata;

      if(fdata == ':') {
        if((fdata = getchar()) == '=') {
          raw_token[raw_token_idx++] = fdata;
        }
      }

      if(isSymbol(raw_token)) {
        token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
        token.type = SYMBOL;
        assign(token.data, raw_token);
        tokens[tokens_quantity++] = token;
      }

      raw_token_idx = 0;
      reset(raw_token); 
    }
    else if(isalpha(fdata)) {
      raw_token[raw_token_idx++] = fdata;
    }
    else if(isdigit(fdata)) {
      raw_token[raw_token_idx++] = fdata;
    } 
    else if(fdata == ' ' || fdata == ';' || fdata == '\t') {
      raw_token[raw_token_idx] = '\0';

      if(isWord(raw_token)) {
        token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
        token.type = WORD;
        token.line = line_counter;
        assign(token.data, raw_token);
        tokens[tokens_quantity++] = token;
      }
      else if (isNumber(raw_token)) {
        token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
        token.type = NUM;
        token.line = line_counter;
        assign(token.data, raw_token);
        tokens[tokens_quantity++] = token;
      }
      else if(isSymbol(raw_token)) {
        token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
        token.type = SYMBOL;
        token.line = line_counter;
        assign(token.data, raw_token);
        tokens[tokens_quantity++] = token;
      } else if(isIdentifier(raw_token)) {
        token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
        token.type = IDENTIFIER;
        token.line = line_counter;
        assign(token.data, raw_token);
        tokens[tokens_quantity++] = token;
      }

      if(fdata == ';') {
        token.data = malloc(sizeof(char));
        token.type = SYMBOL;
        token.line = line_counter;
        assign(token.data, ";");
        tokens[tokens_quantity++] = token;
      }

      raw_token_idx = 0;
      reset(raw_token);
    }
    else {
      token.data = malloc(sizeof(char) * getLength(raw_token) + 1);
      token.type = UNKNOWN;
      token.line = line_counter;
      assign(token.data, raw_token);
      tokens[tokens_quantity++]= token;

      raw_token_idx = 0;
      reset(raw_token);
    }
  }

  for (int i = 0; i < tokens_quantity; i++) {
    printf("%s na Linha %d: %s\n", getTokenType(tokens[i].type), tokens[i].line, tokens[i].data);
  }

  return 0;
}

size_t getLength(const char* str) {
  size_t len = 0;

  while (*str != '\0') {
    len++;
    str++;
  }

  return len;
}

int isEqual(const char* str1, const char* str2) {
  while (*str1 != '\0' && *str2 != '\0') {
    if (*str1 != *str2) return (*str1 - *str2);

    str1++;
    str2++;
  }

  return (*str1 - *str2);
}

char* assign(char* dest, const char* src) {
  char* ptr = dest;
  while (*src != '\0') {
    *ptr++ = *src++;
  }

  *ptr = '\0';
  return dest;
}

void reset(void* ptr) {
  char* p = (char*) ptr;

  for(size_t i = 0; i < TOKEN_LENGTH; i++) {
    *p++ = '\0';
  }

  return;
}

int isSymbol(char *token) {
  for (int i = 0; i < TOTAL_SYMBOLS; i++) {
    if (isEqual(token, symbols[i]) == 0) {
      return 1;
    }
  }

  return 0;
}

int isIdentifier(char *token) {
  int is_alpha = 0;

  for (int i = 0; i < getLength(token); i++) {
    if (isspace(token[i])) {
      return 0;
    }
    if (isalpha(token[i])) {
      is_alpha = 1;
    }
  }

  return is_alpha;
}

int isNumber(char *token) {
  int has_digits = 0;

  for (int i = 0; i < getLength(token); i++) {
    if (isspace(token[i])) {
      return 0;
    }
    if (isdigit(token[i])) {
      has_digits = 1;
    }
  }

  return has_digits;
}

int isWord(char *token) {
  for (int i = 0; i < TOTAL_WORDS; i++) {
    if (isEqual(token, words[i]) == 0) {
      return 1;
    }
  }

  return 0;
}

const char* getTokenType(TokenType type) {
  if(type == WORD)
    return "PALAVRA RESERVADA";
  else if(type == IDENTIFIER)
    return "IDENTIFICADOR";
  else if(type == NUM)
    return "NUMERO";
  else if(type == STR)
    return "STRING";
  else if(type == SYMBOL)
    return "SIMBOLO";
  else if(type == UNKNOWN)
    return "DESCONHECIDO";
  else if(type == LENGTH_ERROR)
    return "LIMITE DE CARACTERES EXCEDIDO";
}