PROJ_NAME=Cmin

LEX=flex
YACC= bison -d
YFLAGS = -d
CC=gcc
CCFLAGS= -lm

$(PROJ_NAME): lex.yy.c comp.tab.c  lib/hashtable.c Cmin.c
	@ echo 'Building Bin using gcc 	 linke:$^ e $< e $@'
	$(CC)  $^ -o $@  $(CCFLAGS)



lex.yy.c: comp.flex 
	@ echo 'Building flex 	 linke:$^ e $< e $@'
	$(LEX) $^

comp.tab.c: comp.y
	@ echo 'Building Bison 	 linke:$^ to $@'
	$(YACC) $^  

clean:
	@ echo 'Remove filles'
	@rm  comp.tab.h lex.yy.c comp.tab.c
	
.PHONY: clean