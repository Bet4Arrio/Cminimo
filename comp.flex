%{
	#include "comp.tab.h"
	int yyerror(char *msg);
	int linha=1;
	int coluna=1;
%}

%%
[ \t]			{ coluna+=yyleng; }
\n			{ coluna = 1; linha++;}
";"			{ coluna+=yyleng; return PONTO_E_VIRGULA; }
","			{ coluna+=yyleng; return VIRGULA; }
"{"			{ coluna+=yyleng; return ABRE_CHAVES; }
"}"			{ coluna+=yyleng; return FECHA_CHAVES; }
")"			{ coluna+=yyleng; return FECHA_PARENTESES; }
"("			{ coluna+=yyleng; return ABRE_PARENTESES; }
"+"			{ coluna+=yyleng; return MAIS; }
"-"			{ coluna+=yyleng; return MENOS; }
"/"			{ coluna+=yyleng; return DIVIDIR; }
"*"			{ coluna+=yyleng; return MULTIPLICA; }
"if"		{ coluna+=yyleng; return IF; }
"else"		{ coluna+=yyleng; return ELSE; }
">"			{ coluna+=yyleng; return MAIORQUE; }
"<"			{ coluna+=yyleng; return MENORQUE; }
"="			{ coluna+=yyleng; return INGUAL; }
"!"			{ coluna+=yyleng; return NAO; }
"&&"			{ coluna+=yyleng; return AND; }
"||"			{ coluna+=yyleng; return OR; }
"int"		{ coluna+=yyleng; return INT; }
"while"		{ coluna+=yyleng; return WHILE; }
"main"		{ coluna+=yyleng; return MAIN; }
"return"	{ coluna+=yyleng; return RETURN; }
[0-9]+		{ coluna+=yyleng; yylval.number = atoi(yytext); return NUM; }
([a-zA-Z])([_a-zA-Z0-9]+) 	{ coluna+=yyleng; yylval.string = strdup(yytext); return VARIAVEL; }
"//".*\n			{ coluna+=yyleng; }		
.					{ yyerror("erro lexico"); }
%%
int yywrap(){
	return -1;
}

