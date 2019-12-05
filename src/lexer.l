%{
    #include <iostream>
    #include <string>
    #include <cstdlib>
    #include <stack>
    #include <queue>
    #include <deque>
    #include "parser.hpp"

    #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
    #define PRINT(a) std::cout << a << std::endl
    #define POP if(!to_return.empty()){\
                    int val = to_return.front();\
                    if(ScannerMessages) std::cerr << "Dedent" << std::endl;\
                    to_return.pop();\
                    return val;\
                }

    std::stack<int> indent_depth; // init stack with one 0 element
    std::queue<int> to_return;
    
    #ifdef ScannerDebug
        bool ScannerMessages = true;
    #else
        bool ScannerMessages = false;
    #endif
%}

%option nodefault
%option yylineno
%option noyywrap

%%

%{
    if(indent_depth.empty()){
        indent_depth.push(0);
    }
    POP;
%}

^[ \t]*\r?\n           { /*Ignore empty lines*/ }
^[ \t]*[/][/].*\r?\n   { /*skip whole line comments*/ }
[/][/].*$              { /* skip comments on same line as a statement*/ }
^[ \t]+   {
    if(!indent_depth.empty() && indent_depth.top() < yyleng){
        indent_depth.push(yyleng);
        if(ScannerMessages) std::cerr << "Indent" << std::endl;
        return INDENT;
    } else {
        printf("dedents should start coming here %d\n", yyleng);
        while(!indent_depth.empty() && indent_depth.top() != yyleng){
            indent_depth.pop();
            to_return.push(DEDENT);
        } 
        if(indent_depth.empty()){
            std::cerr << "Error: incorrect indentation on line " << yylineno << std::endl;
            return 1;
        }
        POP;
    }

}
^[^ \t\r\n]+ {
    while(!indent_depth.empty() && indent_depth.top() != 0){
        indent_depth.pop();
        to_return.push(DEDENT);
    }
    for(int i = strlen(yytext); i > 0; i--){
        unput(yytext[i-1]);
    }
    POP;
}

\r?\n { if(ScannerMessages) std::cerr << "Newline" << std::endl; return NEWLINE; }

<<EOF>> {
    while(!indent_depth.empty() && indent_depth.top() != 0){
        indent_depth.pop();
        to_return.push(DEDENT);
    }
    POP;
    yyterminate();
}

[ \t]       //ignore spaces above that werent handled

"Game"    { if(ScannerMessages) std::cerr << "Game" << std::endl; return GAME; } 
"Players" { if(ScannerMessages) std::cerr << "Players" << std::endl; return PLAYERS; } 
"Player"  { if(ScannerMessages) std::cerr << "Player" << std::endl; return PLAYER; } 
"Board"   { if(ScannerMessages) std::cerr << "Board" << std::endl; return BOARD; }
"Piece"   { if(ScannerMessages) std::cerr << "Piece" << std::endl; return PIECE; }
"Turn"    { if(ScannerMessages) std::cerr << "Turn" << std::endl; return TURN; }
"Win"     { if(ScannerMessages) std::cerr << "Win" << std::endl; return WIN; }
"End"     { if(ScannerMessages) std::cerr << "End" << std::endl; return END; }

[0-9]+ {
    yylval.Num = atoi(yytext);
    if(ScannerMessages) std::cerr << "Int_Lit" << std::endl;
    return INT_LIT;
}

[a-zA-Z]+ {
    yylval.Str = new std::string(yytext); 
    if(ScannerMessages) std::cerr << "Str_Lit" << std::endl;
    return STR_LIT;
}

. {
    std::cout << "ERROR line " << yylloc.first_line << ": " << "Unexpected character" << yytext << std::endl;
}
%%
