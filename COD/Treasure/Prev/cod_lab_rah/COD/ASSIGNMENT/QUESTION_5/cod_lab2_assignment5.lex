SIGN [+-] 
DIGIT [0-9] 

%%
 
{SIGN}?{DIGIT}+ {
     printf("This is an Integer: %s \n",yytext);
 }
 {SIGN}?{DIGIT}+"."{DIGIT}+ {
    printf("This is a float: %s \n",yytext);
 }
%%
 
main(){
  printf("enter the input in float or integer format");
  yylex();
}

