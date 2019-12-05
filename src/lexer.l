%{
    #include <iostream>
    #include <string>
    #include <cstdlib>
    #include "parser.hpp"

    #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
    #define PRINT(a) std::cout << a << std::endl
%}

%option nodefault
%option yylineno
%option noyywrap

%%
[ \t]                   // Ignore Whitespace
[/]{2}.*[\n\r]          // Ignore comments
^[ \t]*[\n\r]+          // Ignore empty lines

"Game"    { return GAME; } 
"Players" { return PLAYERS; } 
"Player"  { return PLAYER; } 
"Board"   { return BOARD; }
"Piece"   { return PIECE; }
"Turn"    { return TURN; }
"Win"     { return WIN; }
"End"     { return END; }

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
    std::cout << "ERROR line " << yylloc.first_line << ": " << "Unexpected character" << yytext << std::endl;
}
%%
