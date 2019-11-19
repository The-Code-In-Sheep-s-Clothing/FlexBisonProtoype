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
    ast::PieceBlock * PieceBlock;
}

/* Primitives  */
%token <Num> INT_LIT
%token <Str> STR_LIT
%token <Boolean> BOOL_LIT

/* Top-level Statement types */
%token GAME PLAYERS PLAYER BOARD PIECE TURN WIN

/* Piece actions */
%token PLACE
/* TODO */
/* %token MOVE */
/* %token REMOVE */

/* Other tokens */
%token NEWLINE

/* Rule types */
%type <Block> stmt_list piece_block /* turn_block win_block */
%type <PieceBlock> piece_block_stmt_list /* turn_block_stmt_list win_block_stmt_list */
%type <Stmt> stmt game_stmt players_stmt board_stmt
%type <Stmt> piece_block_stmt  /*turn_block_stmt win_block_stmt */

%start program

%parse-param {ast::Block ** ast_root}

%%

program
    : stmt_list {*ast_root = $1; }
    ;

stmt_list
    : stmt { $$ = new ast::Block(std::shared_ptr<ast::Statement>($1)); }
    | stmt_list stmt { $1->add(std::shared_ptr<ast::Statement>($2)); $$ = $1; }
    ;

stmt
    : game_stmt
    | players_stmt
    | board_stmt
    | piece_block { $$ = (ast::Statement *)$1; }
    /* | turn_block { $$ = (ast::Statement *)$1; } */
    /* | win_block { $$ = (ast::Statement *)$1; } */
    ;

game_stmt: GAME STR_LIT NEWLINE {
    $$ = new ast::GameStatement(ast::StringNode(*$2));
};
players_stmt: PLAYERS INT_LIT NEWLINE {
    $$ = new ast::PlayersStatement(ast::NumberNode($2));
};
board_stmt: BOARD STR_LIT INT_LIT INT_LIT NEWLINE { 
    $$ = new ast::BoardStatement(ast::StringNode(*$2),
                                 ast::NumberNode($3),
                                 ast::NumberNode($4)); 
};
/* Piece block */
piece_block: PIECE STR_LIT INT_LIT '{' NEWLINE piece_block_stmt_list '}' NEWLINE { 
    $6->set_name(ast::StringNode(*$2));
    $6->set_num(ast::NumberNode($3));
    $$ = $6; 
};

piece_block_stmt_list
    : piece_block_stmt { $$ = new ast::PieceBlock(std::shared_ptr<ast::Statement>($1)); }
    | piece_block_stmt_list piece_block_stmt { $1->add(std::shared_ptr<ast::Statement>($2)); $$ = $1; }
    ;

piece_block_stmt: PLAYER INT_LIT STR_LIT NEWLINE { 
    $$ = new ast::PlayerPieceStatement(ast::NumberNode($2), ast::StringNode(*$3)); 
};

/* Turn block */
/* turn_block: {}; */
/* turn_block: TURN '{' '}' {}; */
/*  */
/* turn_block_stmt_list */
/*     : turn_block_stmt {} */
/*     | turn_block_stmt_list {} */
/*     ; */
/*  */
/* Win Block */
/* win_block: {}; */
/* win_block: WIN STR_LIT '{' '}' {}; */
/*  */
/* win_block_stmt_list */
/*     : win_block_stmt {} */
/*     | win_block_stmt_list {} */
/*     ; */

%%

void yyerror(ast::Block **ast, const char* err) {
    std::cerr << "Parser error: " << err << std::endl;
}
