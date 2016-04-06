#include "lexer.h"
//
// generates the lexer's output
//   t: the token
//   tval: token value
//
void lexer_emit(int t, int tval) {  

  switch(t) {
    case IF:
      printf("IF\n"); 
      break;
    case NUM:
      printf("NUM.%d\n", tval); 
      break;
    default:
      printf("token %c\n", tval); 
      break;
  }
}
