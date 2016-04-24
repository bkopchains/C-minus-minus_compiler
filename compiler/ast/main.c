//
// An example program that uses the ast library.
// This builds the ast top-down, however, when you build an ast
// as part of the parsing step, you will be building it from the
// leaf nodes up.
//
// (thanks to Tia Newhall)
//
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

#define TOKEN0  0 
#define TOKEN1  1 
#define TOKEN2  2 
#define TOKEN3  3 
#define TOKEN4  4 
#define TOKEN5  5 
#define TOKEN6  6 
#define TOKEN7  7 
#define TOKEN8  8 
#define TOKEN9  9 

#define NONTERM 100 
#define PROGRAM 101
#define FUNCTION 102
#define NONE 0
#define FUNCSTR "Function"  
#define PROGSTR "Program"  

static char *token_strings[] = { 
                        "Token 0", "Token 1", "Token 2", "Token 3",
                        "Token 4", "Token 5", "Token 6", "Token 7",
                        "Token 8", "Token 9"
                };

void print_token(ast_info *t);

int main(int argc, char *argv[]) {

  ast atree;
  int i, j, k, p;
  ast_info *s;
  ast_node *n;
  char lexeme[MAX_LEXEME_SIZE];

  // create and init new ast node
  s = create_new_ast_node_info(NONTERM, 0, PROGRAM, 0, 0);
  n = create_ast_node(s);
  init_ast(&atree, n);

  for(i=0; i < 3; i++) {
        sprintf(lexeme, "t_%d", i);  
        s = create_new_ast_node_info(i, i, NONE,lexeme,0);
        n = create_ast_node(s);
        if(s == NULL || n==NULL) { printf("ERROR token create\n"); exit(1); }
        add_child_node(atree.root, n);
  }

  for(i=0; i < 3; i++) {
    for(j=0; j < 8; j++) {
        sprintf(lexeme, "t_%d_%d", i,j);  
        s = create_new_ast_node_info(j, i*10+j, NONE, lexeme, 0);
        n = create_ast_node(s);
        if(s == NULL || n==NULL) { printf("ERROR token create\n"); exit(1); }
        add_child_node((atree.root->childlist[i]), n);

        for(k=0; k < 5; k++) {
          sprintf(lexeme, "t_%d_%d_%d", i,j,k);  
          s = create_new_ast_node_info(k, (i*100)+j*10+k, NONE, lexeme, 0);
          n = create_ast_node(s);
          if(s==NULL || n==NULL) { printf("ERROR token create\n"); exit(1); }
          add_child_node((atree.root->childlist[i]->childlist[j]), n);
          for(p=0; p < 4; p++) {
            sprintf(lexeme, "t_%d_%d_%d_%d", i,j,k,p);  
            s = create_new_ast_node_info(p,(i*1000+j*100+k*10+p),NONE,lexeme,0);
            n = create_ast_node(s);
            if(s==NULL || n==NULL){printf("ERROR token create\n"); exit(1);}
            // in a parser, you would be in a call to a parser function
            // that takes a pointer to the current ast node or to its
            // parent, so you would not have this really long string of .'s 
            // to access the right node to pass to add_child_node:
            add_child_node(
                atree.root->childlist[i]->childlist[j]->childlist[k], n);
          }
        }
    }
  }

  // let's just add another one that could be how you would 
  // add one for a non-terminal grammar symbol
  s = create_new_ast_node_info(NONTERM, 0, FUNCTION, 0, 0);
  n = create_ast_node(s);
  add_child_node(atree.root, n);
         
  print_ast(atree, print_token); 

  // clean up all malloced ast state
  destroy_ast(&atree); 
  exit(0);
}


//**********************************************************************
// This is a print function that is passed to the ast_print function.
// The user of the ast library provides this function since the
// particular tokens are defined by the user and will likely differ
// from one source to another...the ast library is more generic this
// way.  Your print function must have the same prototye as this one.
void print_token(ast_info *t) {

  if(t != NULL) {

    if((t->token <= TOKEN9) && (t->token >= TOKEN0)) {
        printf("%s:%d", token_strings[t->token], t->value); 
    }

    else if ((t->token == NONTERM)) {
      if(t->grammar_symbol == FUNCTION){
        printf("%s:%d", FUNCSTR, t->value);
      } else if(t->grammar_symbol == PROGRAM){
        printf("%s:%d", PROGSTR, t->value);
      } else {
        printf("unknown token");
      }
    }
    else {
      printf("unknown token");
    }
  }
  else {
    printf("NULL token\n");
  }
  if(strlen(t->lexeme)) {
        printf(":%s", t->lexeme);
  }
}

