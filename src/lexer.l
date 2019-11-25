%{
    #include <iostream>
    #include <string>
    #include <cstdlib>
    #include <stack>
    #include <queue>
    //#include "parser.hpp"

    #define PRINT(a) std::cout << a << std::endl
    using namespace std;
    stack <int> s;
    std::queue<int> q;

%}

%option nodefault
%option yylineno
%option noyywrap

%%

%{
  /*
   * These lines go at the top of the lexing function.  We only want to
   * initialize the indentation level stack once by pushing a 0 onto it (the
   * indentation stack should never be empty, except immediately after it is
   * created).
   */
  if (s.empty()) {
    s.push(0);
  }
  if(!q.empty()){
      int temp = q.front();
      q.pop();

      return(yylval.category = temp);
  }
%}


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

^[^ \t\n]+ {

        yyleng = 0;
        if(yyleng == s.top()){

        }else{
          while(s.top() != 0){
              q.push(DEDENT);
              s.pop();
          }
          for(int i = strlen(yytext); i > 0; i--){
              unput(yytext[i-1]);
          }
          int temp = q.front();
          q.pop();

          return(yylval.category = temp);
          REJECT;
    }
}

^[ \t]+ {
    if(yyleng == s.top()){

    }else{
        if(yyleng > s.top()){
            s.push(yyleng);
            return(yylval.category = INDENT);

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
                    q.push(DEDENT);
                }
                int temp = q.front();
                q.pop();
                return (yylval.category = temp);
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
        q.push(DEDENT);
        s.pop();
    }
    if(!q.empty()){
      int temp = q.front();
      q.pop();
      return (yylval.category = temp);
    }
    return 0;
}

. {
    PRINT("Unexpected Character");
}
%%
