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
      printf("NUM.%c\n", tval); 
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
      printf("ID.%d\n", tval);
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
    case ';':
      printf("SEMICOL\n");
      break;
    case ':':
      printf("COLON\n");
      break;
    case ',':
      printf("COMMA\n");
      break;
    case '+':
      printf("PLUS\n");
      break;
    case '-':
      printf("MINUS\n");
      break;
    case DIVIDE:
      printf("DIVIDE\n");
      break;
    case '*':
      printf("MULT\n");
      break;
    case '(':
      printf("LPAREN\n");
      break;
    case ')':
      printf("RPAREN\n");
      break;  
    case '{':
      printf("LBRAC\n");
      break;
    case '[':
      printf("LSQBRAC\n");
      break;
    case ']':
      printf("RSQBRAC\n");
      break;
    case '}':
      printf("RBRAC\n");
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
    default:
      printf("token %c\n", tval); 
      break;
  }
}
