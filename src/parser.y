%{
    #include <iostream>
    #include <string>
    #include "parser.hpp"

    extern int yylex();
    void yyerror(ast::Block**, const char* err);
%}

%locations

%code requires {
    #include "ast.hpp"
}

%union {
    int Num;
    bool Boolean;
    std::string * Str;
    ast::Statement * Stmt;
    ast::Block * Block;
}

/* Primitives  */
%token <Num> INT_LIT
%token <Str> STR_LIT
%token <Boolean> BOOL_LIT

/* Top-level Statement types */
%token GAME PLAYERS BOARD PIECE TURN WIN 

/* Piece actions */
%token PLACE
/* TODO */
/* %token MOVE */
/* %token REMOVE */

/* Other tokens */
%token NEWLINE

/* Rule types */
%type <Block> stmt_list
%type <Stmt> stmt game_stmt players_stmt board_stmt turn_stmt win_stmt

%start program

%parse-param {ast::Block ** ast_root}

%%

program
    : stmt_list {*ast_root = new ast::Block(std::string("test")); }
    ;

stmt_list
    : stmt { $$ = new ast::Block(); }
    | stmt stmt_list { $$ = new ast::Block(); }
    ;

stmt
    : game_stmt
    | players_stmt
    | board_stmt
    | turn_stmt
    | win_stmt
    ;

game_stmt: GAME STR_LIT NEWLINE {};
players_stmt: PLAYERS INT_LIT NEWLINE {};
board_stmt: BOARD STR_LIT INT_LIT INT_LIT NEWLINE {};
turn_stmt: TURN '{' '}' {};
win_stmt: WIN STR_LIT '{' '}' {};

%%

void yyerror(ast::Block **ast, const char* err) {
    std::cerr << "Parser error: " << err << std::endl;
}
