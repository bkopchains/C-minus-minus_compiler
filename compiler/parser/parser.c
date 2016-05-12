/*
 * parser.c: A Recursive Descent Parser for C--
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"

// TODO: you may completely wipe out or change the contents of this file; it
//       is just an example of how to get started on the structure of the 
//       parser program.

static void program(FILE *fd, ast_node *parent);
static void parser_error(char *err_string);
void PROG1(FILE *fd);
void PROG2(FILE *fd);
void FDL1(FILE *fd);
void PDL(FILE *fd);
void PDL1(FILE *fd);
void PDL2(FILE *fd);
void BLOCK(FILE *fd);
void VDL(FILE *fd);
void VDL1(FILE *fd);
void epsilon(FILE *fd);
void StmtList(FILE *fd);
void Stmt(FILE *fd);


void FDL(FILE *fd);
void E5(FILE *fd);
void E5PRIME(FILE *fd);
void E6(FILE *fd);
void E6PRIME(FILE *fd);
void E7(FILE *fd);
void E8(FILE *fd);
void E8PRIME(FILE *fd);
void ExprList(FILE *fd);
void ELPRIME(FILE *fd);


char lookahead;  // stores next token returned by lexer
                // you may need to change its type to match your implementation
                
ast ast_tree;   // the abstract syntax tree
// void PROG();
// void PROG1();
// void PROG2();
// void FDL1();
// void FDL();
// void VDL();
// void VDL1();
// void PDL();
// void PDL1();
// void PDL2();

/**************************************************************************/
/*
 *  Main parser routine: parses the C-- program in input file pt'ed to by fd, 
 *                       calls the function corresponding to the start state,
 *                       checks to see that the last token is DONE,
 *                       prints a success msg if there were no parsing errors
 *  param fd: file pointer for input
 */
void parse(FILE *fd)  {

  // TODO: here is an example of what this function might look like, 
  //       you may completely change this:
  ast_info *s;
  ast_node *n;


  // create the root AST node
  s = create_new_ast_node_info(NONTERMINAL, 0, ROOT, 0, 0);
  n = create_ast_node(s);
  if(init_ast(&ast_tree, n)) {
        parser_error("ERROR: bad AST\n");
  }

  // lookahead is a global variable holding the next token
  // you could also use a local variable and then pass it to program
  lookahead = lexan(fd);
  program(fd, ast_tree.root);  // program corresponds to the start state

  /*
  // the last token should be DONE
  if (lookahead != DONE) {
    parser_error("expected end of file");   
  } else {
     match(DONE, fd);
  }
  */
}
/**************************************************************************/
static void parser_error(char *err_string) {
  if(err_string) {
    printf("%s\n", err_string);
  }
  exit(1);
}  
/**************************************************************************/
/*
 *  this function corresponds to the start symbol in the LL(1) grammar
 *  when this function returns, the full AST tree with parent node "parent"
 *  will be constructed
 *         fd: the input stream
 *     parent: the parent ast node  (it should be a ROOT)
 */
static void program(FILE *fd, ast_node *parent) {

  if(lookahead == INT || lookahead == CHAR){
    if(lookahead == INT){
      printf("MATCH: INT\n");
    }
    else{
      printf("MATCH: CHAR\n");
    }
    //printf("MATCH: %c\n", lookahead);
    lookahead = lexan(fd);
    if(lookahead == ID){
      printf("MATCH: ID.%s\n", lexbuf);
      lookahead = lexan(fd);
      PROG1(fd);
    }
    else{
      printf("Error: Unexpexted Symbol\n");
    }
  }
  else{
    printf("Error: Unexpexted Symbol\n");
  }
}

//PROG1 -> ; PROG| [num]; PROG | PROG2;
void PROG1(FILE *fd){

  if(lookahead == SEMICOL){
    printf("MATCH: SEMICOL\n");
    lookahead = lexan(fd);
    program(fd, lookahead);
  }
  else if (lookahead == LBRACK){
    printf("MATCH: LBRACK\n");
    lookahead = lexan(fd);
    if (lookahead == NUM){
      printf("MATCH: NUM.%c\n", lexbuf);
      lookahead = lexan(fd);
      if(lookahead == RBRACK){
        printf("MATCH: RBRACK\n");
        lookahead = lexan(fd);
        if(lookahead == SEMICOL){
          printf("MATCH: SEMICOL\n");
          lookahead = lexan(fd);
          program(fd, lookahead);
        }
        else{
          printf("Error: Unexpexted Symbol\n");
        }
      }
      else{
        printf("Error: Unexpexted Symbol\n");
      }
    }
    else{
      printf("Error: Unexpexted Symbol\n");
    }
  }
  else{
    //lookahead = lexan(fd);
    PROG2(fd);
  }  
}

//PROG2 -> ( FDL1
void PROG2(FILE *fd){
  //lookahead = lexan(fd);
  if(lookahead == LPAREN){
    printf("MATCH: LPAREN\n");
    lookahead = lexan(fd);
    FDL1(fd);
  }
  else{
    printf("Error: Unexpexted Symbol");
  }
}

//FDL1 -> PDL ) { BLOCK FDL
void FDL1(FILE *fd){
  PDL(fd);
  if (lookahead == RPAREN){
    printf("MATCH: RPAREN\n");
    lookahead = lexan(fd);
    if (lookahead == LBRACE){
      printf("MATCH: LBRACE\n");
      lookahead = lexan(fd);
      BLOCK(fd);
      lookahead = lexan(fd);
      //FDL(fd);
    }
    else{
      printf("Error: Unexpexted Symbol");
    }
  }
  else{
    //printf("Error: Unexpexted Symbol");
  }
}

//PDL -> char id PDL1 | int id PDL1 | epsilon
void PDL(FILE *fd){
  if(lookahead == CHAR || lookahead == INT){
    if(lookahead == CHAR){
      printf("MATCH: CHAR\n");
    }
    else{
      printf("MATCH: INT\n");
    }
    lookahead = lexan(fd);
    if(lookahead == ID){
      printf("MATCH: ID.%s\n", lexbuf);
      lookahead = lexan(fd);
      PDL1(fd);
    }
    else{
      printf("Error: Unexpexted Symbol");
    }
  }
  else{
    epsilon(fd);
  }
}

//PDL1 -> [ ] PDL2 | PDL2
void PDL1(FILE *fd){
  if(lookahead == LBRACK){
    printf("MATCH: LBRACK\n");
    lookahead = lexan(fd);
    if(lookahead == RBRACK){
      printf("MATCH: RBRACK\n");
      lookahead = lexan(fd);
      PDL2(fd);
    }
    else{
      printf("Error: Unexpexted Symbol");
    }
  }
  else{
    PDL2(fd);
  }
}

//PDL2 -> , PDL2 | PDL2
void PDL2(FILE *fd){
  if(lookahead == COMMA){
    printf("MATCH: COMMA\n");
    lookahead = lexan(fd);
    PDL(fd);
  }
  else{
    epsilon(fd);
  }
}

//BLOCK -> VDL StmtList }
void BLOCK(FILE *fd){
  VDL(fd);
  //StmtList1(fd);
  if (lookahead == RBRACE){
    printf("MATCH: RBRACE\n");
    lookahead = lexan(fd);
  }
  else{
    printf("ERROR: Unexpexted Symbol");
  }
}

//VDL -> int id VDL1 | char id VDL1 | epsilon
void VDL(FILE *fd){
  if (lookahead == INT || lookahead == CHAR){
    if(lookahead == INT){
      printf("MATCH: INT\n");
    }
    else{
      printf("MATCH: CHAR\n");
    }
    lookahead = lexan(fd);
    if(lookahead == ID){
      printf("MATCH: ID.%s\n", lexbuf);
      lookahead = lexan(fd);
      VDL1(fd);
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }
  else{
    epsilon(fd);
  }
}

//VDL1 -> ; VDL | [ num ] ; VDL
void VDL1(FILE *fd){
  if (lookahead == SEMICOL){
    printf("MATCH: SEMICOL\n");
    lookahead = lexan(fd);
    VDL(fd);
  }
  else if(lookahead == LBRACK){
    printf("MATCH: LBRACK\n");
    lookahead = lexan(fd);
    if(lookahead == NUM){
      printf("MATCH: NUM.%c\n", lexbuf);
      lookahead = lexan(fd);
      if(lookahead == RBRACK){
        printf("MATCH: RBRACK\n");
        lookahead = lexan(fd);
        if(lookahead == SEMICOL){
          printf("MATCH: SEMICOL\n");
          lookahead = lexan(fd);
          VDL(fd);
        }
        else{
          printf("ERROR: Unexpexted Symbol");
        }
      }
      else{
        printf("ERROR: Unexpexted Symbol");
      }
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }
  else{
    //Don't know if i need 
    printf("ERROR: Unexpexted Symbol");
  }
}


void epsilon(FILE *fd){
  printf("epsilon\n");
}

void StmtList(FILE *fd){
  Stmt(fd);
  //lookahead == lexan(fd);
  //StmtList1(fd);
}

void Stmt(FILE *fd){
  if(lookahead == SEMICOL){
    printf("MATCH: SEMICOL\n");
    lookahead = lexan(fd);
  }

  else if(lookahead == RETURN){
    printf("MATCH: KEYWORD.%s\n", lexbuf);
    lookahead = lexan(fd);
    //Expr();
    //lookahead = lexan(fd);
    if (lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }


  else if(lookahead == READ){
    printf("MATCH: KEYWORD.%s\n", lexbuf);
    lookahead = lexan(fd);
    if(lookahead == ID){
      printf("MATCH: ID.%s\n", lexbuf);
      lookahead = lexan(fd);
      if(lookahead == SEMICOL){
        printf("MATCH: SEMICOL\n");
        lookahead = lexan(fd);
      }
      else{
        printf("ERROR: Unexpexted Symbol");
      }
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }


  else if(lookahead == WRITE){
    printf("MATCH: KEYWORD.%s\n", lexbuf);
    lookahead = lexan(fd);
    //Expr(fd);
    //lookahead = lexan(fd);
    if (lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }

  else if(lookahead == WRITELN){
    printf("MATCH: KEYWORD.%s\n", lexbuf);
    lookahead = lexan(fd);
    if(lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }

  else if(lookahead == BREAK){
    printf("MATCH: KEYWORD.%s\n", lexbuf);
    lookahead = lexan(fd);
    if(lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }

  else if (lookahead == IF){
    printf("MATCH: KEYWORD.%s\n", lexbuf);
    lookahead = lexan(fd);
    if(lookahead == LPAREN){
      printf("MATCH: LPAREN\n");
      lookahead = lexan(fd);
      //Expr(fd);
      //lookahead = lexan(fd);
      if(lookahead == RPAREN){
        printf("MATCH: RPAREN\n");
        lookahead = lexan(fd);
        //Stmt(fd);
        //lookahead = lexan(fd);
        if(lookahead == ELSE){
          printf("MATCH: KEYWORD.%s\n", lexbuf);
          lookahead = lexan(fd);
          //Stmt(fd);
          //lookahead = lexan(fd);
        }
        else{
          printf("ERROR: Unexpexted Symbol");
        }
      }
      else{
        printf("ERROR: Unexpexted Symbol");
      }
    }
    else{
    printf("ERROR: Unexpexted Symbol");
    }
  }

  else if(lookahead == WHILE){
    printf("MATCH: KEYWORD.%s\n", lexbuf);
    lookahead = lexan(fd);
    if(lookahead == LPAREN){
      printf("MATCH: LPAREN\n");
      lookahead = lexan(fd);
      //Expr(fd);
      //lookahead = lexan(fd);
      if(lookahead == RPAREN){
        printf("MATCH: RPAREN\n");
        lookahead = lexan(fd);
        //Stmt(fd);
        //lookahead = lexan(fd);
      }
      else{
        printf("ERROR: Unexpexted Symbol");
      }
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }

  else if(lookahead == RBRACE){
    printf("MATCH: RBRACE\n");
    lookahead = lexan(fd);
    BLOCK();
    lookahead = lexan(fd);
  }

  else{
    Expr(fd):
    lookahead = lexan(fd);
    if(lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }
}







void FDL(FILE *fd){
  if (lookahead == INT || lookahead == CHAR){
    if(lookahead == INT){
      printf("MATCH: INT\n");
    }
    else{
      printf("MATCH: CHAR\n");
    }
    lookahead = lexan(fd);
    if(lookahead == ID){
      printf("MATCH: ID.%s\n", lexbuf);
      lookahead = lexan(fd);
      if(lookahead == LPAREN){
        printf("MATCH: LPAREN\n");
        lookahead = lexan(fd);
        FDL1(fd);
      }
      else{
        printf("ERROR: Unexpexted Symbol");
      }
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }
  else{
    epsilon(fd);
  }
}

  //E5 -> E6 E5'
// void E5(FILE *fd){
//   E6(fd);
//   lookahead = lexan(fd);
//   E5PRIME(fd);
// }


// //E5' -> + E6 E5' | -E6 E5' | epsilon
// void E5PRIME(FILE *fd){
//   if (lookahead == PLUS){
//     printf("MATCH: PLUS\n");
//     lookahead = lexan(fd);
//     //E6(fd);
//     //lookahead = lexan(fd);
//     E5PRIME(fd);
//   }
//   else if(lookahead == MINUS){
//     printf("MATCH: MINUS\n");
//     lookahead = lexan(fd);
//     //E6(fd);
//     //lookahead = lexan(fd);
//      E5PRIME(fd);
//   }
//   else{
//     epsilon(fd);
//   }
// }

// void E6(FILE *fd){
//   E7(fd);
//   lookahead = lexan(fd);
//   //E6PRIME(fd);
// }

// void E7(FILE *fd){
//   if(lookahead == NOT){
//     printf("MATCH: NOT\n");
//     lookahead = lexan(fd);
//     E7(fd);
//   }
//   else if(lookahead == MINUS){
//     printf("MATCH: MINUS\n");
//     lookahead = lexan(fd);
//     E7(fd);
//   }
//   else{
//     //E8(fd);
//   }
// }

// void E8(FILE *fd){
//   if(lookahead == NUM){
//     printf("MATCH: NUM.%c\n", lexbuf);
//   }
//   else if(lookahead == LPAREN){
//     printf("MATCH: LPAREN\n");
//     lookahead = lexan(fd);
//     //Expr();
//     if (lookahead == RPAREN){
//       printf("MATCH: RPAREN\n");
//     }
//     else{
//       printf("ERROR: Unexpexted Symbol");
//     }
//   }
//   else{
//     if(lookahead == ID){
//       printf("MATCH: ID.%s\n", lexbuf);
//       E8PRIME(fd);
//     }
//   }
// }

// void E8PRIME(FILE *fd){
//   if (lookahead == LPAREN){
//     printf("MATCH: LPAREN\n");
//     lookahead = lexan(fd);
//     //ExprList(fd);
//     if (lookahead == RPAREN){
//       printf("MATCH: RPAREN\n");
//     }
//   }
//   else if(lookahead == LBRACK){
//     printf("MATCH: LBRACK\n");
//       lookahead = lexan(fd);
//       //Expr();
//     }
//   else{
//     epsilon(fd);
//   }
// }

// void ExprList(FILE *fd){
//   Expr(fd);
//   lookahead = lexan(fd);
//   //ELPRIME(fd);
// }





  //parser_debug0("in program\n");

  // assert is useful for testing a function's pre and post conditions 
  //assert(parent->symbol->token == NONTERMINAL);
  //assert(parent->symbol->grammar_symbol == ROOT);


//}

