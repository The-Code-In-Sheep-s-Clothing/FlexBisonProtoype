%{
    #include <iostream>
    #include <string>
    #include <cstdlib>
    #include <stack>
    //#include "parser.hpp"

    #define PRINT(a) std::cout << a << std::endl
    using namespace std;
    stack <int> s;

%}

%option nodefault
%option yylineno
%option noyywrap

%%

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

\n[^ \t\n] {
        cout << "NEWLINE" << endl;
        if(yytext[strlen(yytext) - 1] != '\n'){
            unput(yytext[strlen(yytext) - 1]);
        }
        yyleng = 0;
        if(yyleng == s.top()){

        }else{
            int dedents = -1;
            for(int i = 0; 0 < s.size(); i++){
                if(yyleng == s.top()){
                    dedents = i;
                    break;
                }
                s.pop();

            }

            if(dedents == -1)
                cout << "ERROR, INVALID DEDENT" << endl;
            else{
                for(int i = 0; i < dedents; i++){
                    cout << "DEDENT" << endl;
                }
            }


        }

    }

^[ \t]+ {
    if(yyleng == s.top()){

    }else{
        if(yyleng > s.top()){
            s.push(yyleng);
            cout << "INDENT" << endl;

        }else{

            int dedents = -1;
            for(int i = 0; 0 < s.size(); i++){
                if(yyleng == s.top()){
                    dedents = i;
                    break;
                }
                s.pop();

            }

            if(dedents == -1)
                cout << "ERROR, INVALID DEDENT" << endl;
            else{
                for(int i = 0; i < dedents; i++){
                    cout << "DEDENT" << endl;
                }
            }
        }

    }
}


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

<<EOF>> {
    s.pop();
    while(!s.empty()){
        cout << "DEDENT" << endl;
        s.pop();
    }
    return 0;
}

. {
    PRINT("Unexpected Character");
}
%%
