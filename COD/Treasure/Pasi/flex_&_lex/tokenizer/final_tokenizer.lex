FLOAT	  (([-+]?"."[0-9]+)|([-+]?[0-9]+"."[0-9]+))
INT		  [-+]?[0-9]+
CONSTANT	({FLOAT}|{INT})
OPERATOR	"+"|"-"|"*"|"/"|"="|"<"|">"|"%"|"&"|"++"|"--"|">="|"<="|"+="|"-="|"\="|"*="|"=="|"&&"
STRING   	\"([^\"])*\"
FILE            #include[ \t]*<[a-zA-Z_0-9\/-]+\.h>
KEYWORD         ("auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"return"|"register"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"|"main")
ID              [_A-Za-z][_a-zA-Z0-9]*
DELIM     "("|")"|"["|"]"|"{"|"}"|";"|","
SINGLELINECOMMENT		"//".*
MULTILINECOMMENT		"/*"[^("*/")]*"*/"

%%

[ \t\n]+  // Ignore
{SINGLELINECOMMENT}		// Ignore
{MULTILINECOMMENT}		// Ignore
{CONSTANT} 	printf("%s -> Constant\n",yytext);
{OPERATOR}	printf("%s -> Operator\n",yytext);
{STRING} 	printf("%s -> String\n",yytext);
{FILE}          printf("%s -> Header File\n",yytext);
{KEYWORD}       printf("%s -> Keyword\n",yytext);
{ID}            printf("%s -> Identifier\n",yytext);
{DELIM}	       printf("%s -> Delim\n",yytext);

%%

void main()
{
	yyin = fopen("inp.txt","r");
	yylex();
	fclose(yyin);
}