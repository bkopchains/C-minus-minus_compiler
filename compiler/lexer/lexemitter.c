#include "lexer.h"

/* Updated by Taylor Ellsworth
 * Due Date: 4/20/2016
*/

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
    case ELSE:
      printf("ELSE\n");
      break;
    case WHILE:
      printf("WHILE\n");
      break;
    case BREAK:
      printf("BREAK\n");
      break;
    case RETURN:
      printf("RETURN\n");
      break;
    case INT:
      printf("INT\n");
      break;
    case CHAR:
      printf("CHAR\n");
      break;
    case READ:
      printf("READ\n");
      break;
    case NUM:
      printf("NUM.%d\n", tokenval); 
      break;
    case DONE:
      printf("DONE\n");
      break;
    case WRITE:
      printf("WRITE\n");
      break;
    case WRITELN:
      printf("WRITELN\n");
      break;
     case ID:
      printf("ID.%s\n", lexbuf); 
      break;
    case EQ:
      printf("EQ\n");
      break;
    case AND:
      printf("AND\n");
      break;
    case OR:
      printf("OR\n");
      break;
    case FOR:
      printf("FOR\n");
      break; 
    case SEMICOL:
      printf("SEMICOL\n");
      break;
    case COLON:
      printf("COLON\n");
      break;
    case COMMA:
      printf("COMMA\n");
      break;
    case PLUS:
      printf("PLUS\n");
      break;
    case MINUS:
      printf("MINUS\n");
      break;
    case DIVIDE:
      printf("DIVIDE\n");
      break;
    case MULT:
      printf("MULT\n");
      break;
    case LPAREN:
      printf("LPAREN\n");
      break;
    case RPAREN:
      printf("RPAREN\n");
      break;  
    case LBRACE:
      printf("LBRACE\n");
      break;
    case LBRACK:
      printf("LBRACK\n");
      break;
    case RBRACK:
      printf("RBRACK\n");
      break;
    case RBRACE:
      printf("RBRACE\n");
      break;  
    case LT:
      printf("LT\n");
      break;
    case LE:
      printf("LE\n");
      break;
    case GT:
      printf("GT\n");
      break;
    case GE:
      printf("GE\n");
      break;
    case ASSIGN:
      printf("ASSIGN\n");
      break;
    case NOT:
      printf("NOT\n");
      break;
    case NOTEQ:
      printf("NOTEQ\n");
      break;
    default:
      printf("token %c\n", tval); 
      break;
  }
}
