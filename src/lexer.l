%{
    #include <iostream>
    #include <string>
    #include <cstdlib>
    #include "parser.hpp"

    #define PRINT(a) std::cout << a << std::endl
%}

%option nodefault
%option yylineno
%option noyywrap

%%
[ \t]                   // Ignore Whitespace
[/]{2}.*                // Ignore comments
^[ \t]+[\n\r]+          // Ignore empty lines

"Game"    { return GAME; } 
"Players" { return PLAYERS; } 
"Board"   { return BOARD; }
"Piece"   { return PIECE; }
"Turn"    { return TURN; }
"Win"     { return WIN; }

"{" |
"}" { return yytext[0]; }

[0-9]+ {
    yylval.Num = atoi(yytext);
    return INT_LIT;
}

[a-zA-Z]+ {
    yylval.Str = new std::string(yytext); 
    return STR_LIT;
}

\n {
    return NEWLINE;
}

. {
    PRINT("Unexpected Character");
}
%%
