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
void StmtList1(FILE *fd);
void Expr(FILE *fd);
void E0(FILE *fd);
void E0PRIME(FILE *fd);
void E1(FILE *fd);
void E1PRIME(FILE *fd);
void E2(FILE *fd);
void E2PRIME(FILE *fd);
void E3(FILE *fd);
void E3PRIME(FILE *fd);
void E4(FILE *fd);
void E4PRIME(FILE *fd);
void E5(FILE *fd);
void E5PRIME(FILE *fd);
void E6(FILE *fd);
void E6PRIME(FILE *fd);
void E7(FILE *fd);
void E8(FILE *fd);
void E8PRIME(FILE *fd);
void ExprList(FILE *fd);
void ELPRIME(FILE *fd);
void FDL(FILE *fd);



char lookahead;  // stores next token returned by lexer
                // you may need to change its type to match your implementation
                
ast ast_tree;   // the abstract syntax tree


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
      lookahead = lexan(fd);
      PROG1(fd);
    }
    lookahead = lexan(fd);
    if(lookahead == ID){
      printf("MATCH: ID.%s\n", lexbuf);
      lookahead = lexan(fd);
      PROG1(fd);
    }
    else{
      printf("Error1: Unexpexted Symbol\n");
    }
  }
  else{
    printf("Error2: Unexpexted Symbol\n");
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
      printf("MATCH: NUM.%d\n", tokenval);
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
          printf("Error3: Unexpexted Symbol\n");
        }
      }
      else{
        printf("Error4: Unexpexted Symbol\n");
      }
    }
    else{
      printf("Error5: Unexpexted Symbol\n");
    }
  }
  else{
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
    printf("Error6: Unexpexted Symbol");
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
      FDL(fd);
      printf("RETURNED TO FDL1");
      program(fd, lookahead);
    }
    else{
      printf("Error7: Unexpexted Symbol");
    }
  }
  else{
    //printf("Error8: Unexpexted Symbol");
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
      printf("Error9: Unexpexted Symbol");
    }
  }
  else{
    printf("at PDL epsilon");
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
      printf("Error10: Unexpexted Symbol");
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
    printf("at pdl2 epsilon");
    epsilon(fd);
  }
}

//BLOCK -> VDL StmtList }
void BLOCK(FILE *fd){
  printf("IN BLOCK\n");
  VDL(fd);
  printf("IN BLOCK BEFORE STMLIST");
  StmtList(fd);
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
      printf("ERROR11: Unexpexted Symbol");
    }
  }
  else{
    printf("at vdl epsilon\n");
    epsilon(fd);
  }
}

//VDL1 -> ; VDL | [ num ] ; VDL
void VDL1(FILE *fd){
  if (lookahead == SEMICOL){
    printf("in vdl1 semicol");
    printf("MATCH: SEMICOL\n");
    lookahead = lexan(fd);
    VDL(fd);
  }
  else if(lookahead == LBRACK){
    printf("MATCH: LBRACK\n");
    lookahead = lexan(fd);
    if(lookahead == NUM){
      printf("MATCH: NUM.%d\n", tokenval);
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
          printf("ERROR12: Unexpexted Symbol");
        }
      }
      else{
        printf("ERROR13: Unexpexted Symbol");
      }
    }
    else{
      printf("ERROR14: Unexpexted Symbol");
    }
  }
  else{
    //Don't know if i need 
    printf("ERROR15: Unexpexted Symbol");
  }
}


void epsilon(FILE *fd){
  printf("epsilon\n");
}

void StmtList(FILE *fd){
  printf("in stmt list");
  Stmt(fd);
  //lookahead = lexan(fd);
  StmtList1(fd);
}

void Stmt(FILE *fd){
  //printf("STMT semicol\n");
  //lookahead = lexan(fd);
  if(lookahead == SEMICOL){
    printf("MATCH: SEMICOL\n");
    lookahead = lexan(fd);
  }

  else if(lookahead == RETURN){
    printf("MATCH1: KEYWORD.RETURN\n");
    lookahead = lexan(fd);
    Expr(fd);
    //lookahead = lexan(fd);
    if (lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
    else{
      printf("ERROR16: Unexpexted Symbol\n");
    }
  }
  
  else if(lookahead == READ){
    printf("MATCH: KEYWORD.READ\n");
    lookahead = lexan(fd);
    if(lookahead == ID){
      printf("MATCH: ID.%s\n", lexbuf);
      lookahead = lexan(fd);
      if(lookahead == SEMICOL){
        printf("MATCH: SEMICOL\n");
        lookahead = lexan(fd);
      }
      else{
        printf("ERROR17: Unexpexted Symbol\n");
      }
    }
    else{
      printf("ERROR18: Unexpexted Symbol\n");
    }
  }


  else if(lookahead == WRITE){
    printf("MATCH: KEYWORD.WRITE\n");
    lookahead = lexan(fd);
    Expr(fd);
    //lookahead = lexan(fd);
    if (lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
    else{
      printf("ERROR19: Unexpexted Symbol\n");
    }
  }

  else if(lookahead == WRITELN){
    printf("MATCH: KEYWORD.WRITELN\n");
    lookahead = lexan(fd);
    if(lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
    else{
      printf("ERROR20: Unexpexted Symbol\n");
    }
  }

  else if(lookahead == BREAK){
    printf("MATCH: KEYWORD.BREAK\n");
    lookahead = lexan(fd);
    if(lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
    else{
      printf("ERROR21: Unexpexted Symbol\n");
    }
  }
  
  else if (lookahead == IF){
    printf("MATCH: KEYWORD.IF\n");
    lookahead = lexan(fd);
    if(lookahead == LPAREN){
      printf("MATCH: LPAREN\n");
      lookahead = lexan(fd);
      Expr(fd);
      //lookahead = lexan(fd);
      if (lookahead == RPAREN){
        printf("MATCH: RPAREN\n");
        lookahead = lexan(fd);
        Stmt(fd);
        //lookahead = lexan(fd);
        if(lookahead == ELSE){
          printf("MATCH: KEYWORD.ELSE\n");
          //lookahead = lexan(fd);
          Stmt(fd);
          //lookahead = lexan(fd);
        }
        else{
          printf("ERROR22: Unexpexted Symbol\n");
        }
      }
      else{
        printf("ERROR23: Unexpexted Symbol\n");
      }
    }
    else{
    printf("ERROR24: Unexpexted Symbol\n");
    }
  }

  else if(lookahead == WHILE){
    printf("MATCH: KEYWORD.WHILE\n");
    lookahead = lexan(fd);
    if(lookahead == LPAREN){
      printf("MATCH: LPAREN\n");
      lookahead = lexan(fd);
      Expr(fd);
      lookahead = lexan(fd);
      if(lookahead == RPAREN){
        printf("MATCH: RPAREN\n");
        lookahead = lexan(fd);
        Stmt(fd);
        lookahead = lexan(fd);
      }
      else{
        printf("ERROR25: Unexpexted Symbol\n");
      }
    }
    else{
      printf("ERROR26: Unexpexted Symbol\n");
    }
  }

  else if(lookahead == LBRACE){
    printf("MATCH: LBRACE\n");
    lookahead = lexan(fd);
    BLOCK(fd);
    lookahead = lexan(fd);
  }

  else{
    Expr(fd);
    lookahead = lexan(fd);
    if(lookahead == SEMICOL){
      printf("MATCH: SEMICOL\n");
      lookahead = lexan(fd);
    }
  }
}

void StmtList1(FILE *fd){
  if(lookahead == RBRACE){
    printf("MATCH: RBRACE\n");
    //lookahead = lexan(fd);
  }
  else{
    StmtList(fd);
  }
}

void Expr(FILE *fd){
  E0(fd);
}

void E0(FILE *fd){
  E1(fd);
  printf("in e0\n");
  //lookahead = lexan(fd);
  E0PRIME(fd);
}

void E0PRIME(FILE *fd){
  if (lookahead == ASSIGN){
    printf("MATCH: ASSIGN\n");
    lookahead = lexan(fd);
    Expr(fd);
  }
  else{
    printf("at e0prime epsilon\n");
    epsilon(fd);
  }
}

void E1(FILE *fd){
  E2(fd);
  printf("in e1\n");
  //lookahead = lexan(fd);
  E1PRIME(fd);
}

void E1PRIME(FILE *fd){
  if (lookahead == OR){
    printf("MATCH: OR\n");
    lookahead = lexan(fd);
    E2(fd);
    //lookahead = lexan(fd);
    E1PRIME(fd);
  }
  else{
    printf("at e1prime epsilon\n");
    epsilon(fd);
  }
}

void E2(FILE *fd){
  E3(fd);
  printf("in e2\n");
  //lookahead = lexan(fd);
  E2PRIME(fd);
}

void E2PRIME(FILE *fd){
  if(lookahead == AND){
    printf("MATCH: AND\n");
    lookahead = lexan(fd);
    E3(fd);
    //lookahead = lexan(fd);
    E2PRIME(fd);
  }
  else{
    printf("at e2prime epsilon\n");
    epsilon(fd);
  }
}

void E3(FILE *fd){
  E4(fd);
  printf("in e3\n");
  //lookahead == lexan(fd);
  E3PRIME(fd);
}

void E3PRIME(FILE *fd){
  if (lookahead == EQ){
    printf("MATCH: EQ\n");
    lookahead = lexan(fd);
    E4(fd);
    //lookahead = lexan(fd);
    E3PRIME(fd);
    }
  else if(lookahead == NOTEQ){
    printf("MATCH: NOTEQ\n");
    lookahead = lexan(fd);
    E4(fd);
    //lookahead = lexan(fd);
    E3PRIME(fd);
  }
  else{
    printf("at e3prime epsilon\n");
    epsilon(fd);
  }
}

void E4(FILE *fd){
  E5(fd);
  printf("in e4\n");
  //lookahead = lexan(fd);
  E4PRIME(fd);
}

void E4PRIME(FILE *fd){
  if(lookahead == LT){
    printf("MATCH: LT\n");
    lookahead = lexan(fd);
    E5(fd);
    //lookahead = lexan(fd);
    E4PRIME(fd);
  }
  else if(lookahead == LE){
    printf("MATCH: LE\n");
    lookahead = lexan(fd);
    E5(fd);
    //lookahead = lexan(fd);
    E4PRIME(fd);
  }
  else if(lookahead == GT){
    printf("MATCH: GT\n");
    lookahead = lexan(fd);
    E5(fd);
    //lookahead = lexan(fd);
    E4PRIME(fd);
  }
  else if(lookahead == GE){
    printf("MATCH: GE\n");
    lookahead = lexan(fd);
    E5(fd);
    //lookahead = lexan(fd);
    E4PRIME(fd);
  }
  else{
    printf("at e4prime epsilon\n");
    epsilon(fd);
  }
}

  //E5 -> E6 E5'
void E5(FILE *fd){
  E6(fd);
  //lookahead = lexan(fd);
  E5PRIME(fd);
}

//E5' -> + E6 E5' | -E6 E5' | epsilon
void E5PRIME(FILE *fd){
  if (lookahead == PLUS){
    printf("RIGHT BEFORE PLUS in e5 prime\n");
    printf("MATCH: PLUS\n");
    lookahead = lexan(fd);
    E6(fd);
    //lookahead = lexan(fd);
    E5PRIME(fd);
  }
  else if(lookahead == MINUS){
    printf("MATCH: MINUS\n");
    lookahead = lexan(fd);
    E6(fd);
    //lookahead = lexan(fd);
    E5PRIME(fd);
  }
  else{
    printf("at e5prime epsilon\n");
    epsilon(fd);
  }
}

void E6(FILE *fd){
  E7(fd);
  printf("in e6\n");
  //lookahead = lexan(fd);
  E6PRIME(fd);
}

void E6PRIME(FILE *fd){
  if (lookahead == MULT){
    printf("MATCH: MULT\n");
    lookahead = lexan(fd);
    E7(fd);
    //lookahead = lexan(fd);
    E6PRIME(fd);
  }
  else if(lookahead == DIVIDE){
    printf("MATCH: DIVIDE\n");
    lookahead = lexan(fd);
    E7(fd);
    //lookahead = lexan(fd);
    E6PRIME(fd);
  }
  else{
    printf("at e6prime epsilon\n");
    epsilon(fd);
  }
}

void E7(FILE *fd){
  if(lookahead == NOT){
    printf("MATCH: NOT\n");
    lookahead = lexan(fd);
    E7(fd);
  }
  else if(lookahead == MINUS){
    printf("MATCH: MINUS\n");
    lookahead = lexan(fd);
    E7(fd);
  }
  else{
    //lookahead = lexan(fd);
    printf("HOW DOES THIS WORK\n");
    E8(fd);
  }
}

void E8(FILE *fd){
  if(lookahead == NUM){
    printf("MATCH: NUM.%d\n", tokenval);
    lookahead = lexan(fd);
  }
  else if(lookahead == LPAREN){
    printf("MATCH: LPAREN\n");
    lookahead = lexan(fd);
    Expr(fd);
    if (lookahead == RPAREN){
      printf("MATCH: RPAREN\n");
      lookahead = lexan(fd); //just added
    }
    else{
      printf("ERROR: Unexpexted Symbol");
    }
  }
  else{
    if(lookahead == ID){
      printf("MATCH: ID.%s\n", lexbuf);
      lookahead = lexan(fd);
      E8PRIME(fd);
    }
  }
}

void E8PRIME(FILE *fd){
  if (lookahead == LPAREN){
    printf("MATCH: LPAREN\n");
    lookahead = lexan(fd);
    ExprList(fd);
    if (lookahead == RPAREN){
      printf("MATCH: RPAREN\n");
      lookahead = lexan(fd); //just added
    }
  }
  else if(lookahead == LBRACK){
    printf("MATCH: LBRACK\n");
      lookahead = lexan(fd);
      Expr(fd);
      if(lookahead == RBRACK){
        printf("MATCH: RBRACK\n");
        lookahead = lexan(fd);
      }
    }
  else{
    printf("at e8prime epsilon\n");
    epsilon(fd);
  }
}

void ExprList(FILE *fd){
  Expr(fd);
  ELPRIME(fd);
  printf("in exprlist\n");
  epsilon(fd);
}

void ELPRIME(FILE *fd){
  if(lookahead == COMMA){
    printf("MATCH: COMMA\n");
    lookahead = lexan(fd);
    ExprList(fd);
  }
  else{
    printf("in exprlist\n");
    epsilon(fd);
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
    printf("at fdl epsilon\n");
    epsilon(fd);
  }
}


