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
    ast::Expression * Exp;
    std::vector<std::shared_ptr<ast::Expression>> * ArgList;
}

/* Primitives  */
%token <Num> INT_LIT
%token <Str> STR_LIT
%token <Boolean> BOOL_LIT

/* Top-level Statement types */
%token GAME PLAYERS PLAYER BOARD PIECE TURN WIN END INDENT DEDENT

/* Piece actions */
/* %token PLACE */
/* TODO */
/* %token MOVE */
/* %token REMOVE */

/* Other tokens */
%token NEWLINE

/* Rule types */
%type <Block> stmt_list piece_block turn_block win_block end_block
%type <Block> function_call_list piece_block_stmt_list
%type <Stmt> stmt game_stmt players_stmt board_stmt piece_block_stmt
%type <Exp> expression function_call
%type <ArgList> function_arg_list function_opt_arg_list

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
    | turn_block { $$ = (ast::Statement *)$1; }
    | win_block { $$ = (ast::Statement *)$1; }
    | end_block { $$ = (ast::Statement *)$1; }
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
piece_block: PIECE STR_LIT INT_LIT NEWLINE INDENT piece_block_stmt_list DEDENT { 
    ((ast::PieceBlock *)$6)->set_name(ast::StringNode(*$2));
    ((ast::PieceBlock *)$6)->set_num(ast::NumberNode($3));
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
turn_block: TURN NEWLINE INDENT function_call_list DEDENT {
    $$ = (ast::TurnBlock *)$4;
};

/* Win Block */
win_block: WIN NEWLINE INDENT function_call_list DEDENT {
    $$ = (ast::WinBlock *)$4;
};

/* End Block */
end_block: END NEWLINE INDENT function_call_list DEDENT {
    $$ = (ast::EndBlock *)$4;
};

function_call
    : STR_LIT function_opt_arg_list NEWLINE { $$ = new ast::FunctionCallExpression(ast::StringNode(*$1), *$2); }
    ;

function_opt_arg_list
    : function_arg_list {$$ = $1;}
    | {$$ = new std::vector<std::shared_ptr<ast::Expression>>(); }
    ;

function_call_list
    : function_call { $$ = new ast::Block(std::shared_ptr<ast::Statement>($1)); }
    | function_call_list function_call { $1->add(std::shared_ptr<ast::Statement>($2)); $$ = $1; }
    ;

expression
    : STR_LIT { $$ = new ast::StringNode(*$1); }
    | INT_LIT { $$ = new ast::NumberNode($1); }
    /* | function_call { $$ = $1; } */
    ;

function_arg_list
    : expression { 
            std::vector<std::shared_ptr<ast::Expression>> *temp = new std::vector<std::shared_ptr<ast::Expression>>;
            temp->push_back(std::shared_ptr<ast::Expression>($1));
            $$ = temp;
        }
    | function_arg_list expression { 
            $1->push_back(std::shared_ptr<ast::Expression>($2)); 
            $$ = $1;
        }
    ;

%%

void yyerror(ast::Block **ast, const char* err) {
    std::cerr << "ERROR line " << yylloc.first_line << ": " << err << std::endl;
}
