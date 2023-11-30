PROJ_NAME=Cmin

LEX=flex
YACC= bison -d

CC=gcc
CCFLAGS= -lm



$(PROJ_NAME): lex.yy.c comp.tab.c  lib/hashtable.c lib/stacks.c Cmin.c
	@ echo 'Building Bin using gcc 	 linke:$^ e $< e $@'
	$(CC)  $^ -o $@  $(CCFLAGS)
	@rm comp.tab.h lex.yy.c comp.tab.c



lex.yy.c: comp.flex 
	@ echo 'Building flex 	 linke:$^ e $< e $@'
	$(LEX) $^

comp.tab.c: comp.y
	@ echo 'Building Bison 	 linke:$^ to $@'
	$(YACC) $^  
