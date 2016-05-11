/* Updated by Taylor Ellsworth
 * Due Date: 4/20/2016
 */

/* The lexical analyzer for the C-- Programming Language
 */
// TODO: you are welcome to completely wipe out the contents of this
// file and start from scratch

#include <stdlib.h>
#include <assert.h>
#include "lexer.h"
#include <string.h> /* memset */


// these are likely values that will be needed by the parser, so 
// making them global variables is okay
char lexbuf[MAXLEXSIZE];  // stores current lexeme
int  tokenval=0;          // stores current token's value
                          // (may not used for every token)
int  src_lineno=0;        // current line number in source code input
char *nonIDs[11] = {"else", "if", "for", "while", "break", "return",
  "int", "char", "read", "write", "writeln"};

// function prototypes:
static void print_lineno();  // static limits its scope to only in this .c file

int character; 
int fullnumber;
int isdigit();
char isalpha();
int isalnum();

/***************************************************************************/
/* 
 *  Main lexer routine:  returns the next token in the input 
 *
 *  param fd: file pointer for reading input file (source C-- program)
 *            TODO: you may want to add more parameters
 *
 *  returns: the next token or 
 *           DONE if there are no more tokens 
 *           LEXERROR if there is a token parsing error 
 */
int lexan(FILE *fd) {

  // here is an example of how to use the debug macros defined in lexer.h
  //   uncomment #define DEBUG_LEXER, and recompile to see debug output 
  //   comment #define DEBUG_LEXER, and recompile to see debug output 
  //
  lexer_debug0("in lexan\n");
  lexer_debug1("in lexan, lineno = %d\n", src_lineno);
  lexer_debug1("in lexan, message = %s\n", "hello there");

//int character;
while(character != DONE && character != LEXERROR) 
{
  character = fgetc(fd);
  if(character == ' ' || character == '\t')
  { // strip out white space
    ;
  }
  else if (character == '\n')
  {
    src_lineno = src_lineno + 1;
  }
  else if(character == '/'){
    if((character = fgetc(fd)) == '*'){
      while((character = fgetc(fd))!= '*'){
        ; // strip out block comments
      }
      character = fgetc(fd);
    }
    else if((character  == '/')){
      while((character = fgetc(fd)) != '\n'){
        ;
      }
      character = fgetc(fd);
    }  
    else{
      return DIVIDE;
    }
  }
  
  else if (isdigit(character))
  {
    fullnumber = character - '0';
    character = fgetc(fd);    
    while(isdigit(character = fgetc(fd))){
      fullnumber = 10 * character - '0';
      //fullnumber = fullnumber - '0';
      //character=fgetc(fd);
    }

    printf("NUM.%d\n", character);
    //return NUM;
  }
  
  //if the first character is &, it checks the second character to see if it is &.
  //If it is \&, it returns AND.  If not, it is a lexical error
  else if(character == '&'){
    if((character = fgetc(fd)) == '&'){
      return AND;
    }
    else{
      ungetc(character, fd);
      lexer_error(character, fd);
    }
  }

  //if the first character is |, it checks the second character to see if it is |.
  //If it is |, it returns OR.  If not, it is a lexical error.
  //GT
  else if(character == '|'){
    if((character = fgetc(fd)) == '|'){
      return OR;
    }
    else{
      ungetc(character, fd);
      lexer_error(character, fd);
    }
  }

  //if the first character is <, it checks the second characterto see if it is =.
  //If it is =, it returns LE.  If not, it returns LT
  else if(character == '<'){
    if((character = fgetc(fd)) == '='){
      return LE;
    }
    else{
      ungetc(character, fd);
      return LT;
    }
  }
  
  //if the first character is >, it checks the second character to see if it is =.
  //If it is =, it returns GE.  If not, it returns GT
  else if(character == '>'){
    if((character = fgetc(fd)) == '='){
      return GE;
    }
    else{
      ungetc(character, fd);
      return GT;
    }
  }
  
  //if the first character is =, it checks the second character to see if it is =.
  //If it is =, it returns EQ.  If not, it returns ASSIGN
  else if(character == '='){
    if((character = fgetc(fd)) == '='){
      return EQ;
      }
    
    else{
      ungetc(character, fd);
      return ASSIGN;
    }
  }

  else if(character == ';'){
    return SEMICOL;
  }

  else if(character == ':'){
    return COLON;
  }

  else if(character == ','){
    return COMMA;
  }

  else if(character == '+'){
    return PLUS;
  }

  else if(character == '-'){
    return MINUS;
  }

  else if(character == '*'){
    return MULT;
  }

  else if(character == '('){
    return LPAREN;
  }

  else if(character == ')'){
    return RPAREN;
  }

  else if(character == '{'){
    return LBRACE;
  }

  else if(character == '}'){
    return RBRACE;
  }

  else if(character == ']'){
    return LBRACK;
  }

  else if(character == '['){
    return RBRACK;
  }
  
 //Determines the correct keyword and returns it 
 else if (isalpha(character)){
    char word[100];
    memset(&word[0], 0, sizeof(word));
    char append[2];
    append[0] = character;
    strcat(word,append);
    
    while ((character = getc(fd)) == '_' || isalnum(character)){
      append[0] = character;
      strcat(word,append);
    }
    ungetc(character, fd);

    if (strcmp(word, nonIDs[0]) == 0){
      return ELSE;
    }
    else if (strcmp(word, nonIDs[1]) == 0){
      return IF;
    }
    else if (strcmp(word, nonIDs[2]) == 0){
      return FOR;
    }
    else if (strcmp(word, nonIDs[3]) == 0){
      return WHILE;
    }
    else if (strcmp(word, nonIDs[4]) == 0){
      return BREAK;
    }
    else if (strcmp(word, nonIDs[5]) == 0){
      return RETURN;
    }
    else if (strcmp(word, nonIDs[6]) == 0){
      return INT;
    }
    else if (strcmp(word, nonIDs[7]) == 0){
      return CHAR;
    }
    else if (strcmp(word, nonIDs[8]) == 0){
      return READ;
    }
    else if (strcmp(word, nonIDs[9]) == 0){
      return WRITE;
    }
    else if (strcmp(word, nonIDs[10]) == 0){
      return WRITELN;
    }
    else{
      //tokenval = *word;
      printf("ID.%s\n", word);
      return ID;
    }
  }
  else
  {
    tokenval = NONE;
    return character;
  }
}
}

 
/***************************************************************************/
// A function for demonstrating that functions should be declared static
// if they are to be used only in the file in which they are defined.
// Static limits the scope to only this .c file
static void print_lineno() {
  
  printf("line no = %d\n", src_lineno);

}


