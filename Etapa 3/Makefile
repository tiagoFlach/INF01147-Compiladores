#
#
# UFRGS - Compiladores B - Marcelo Johann - 2022/1
# 
# Tiago Lucas Flach <tlflach@inf.ufrgs.br>
# Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
# 
#
TEST=0
MAIN=main
OUT=etapa3
HASH=hash
LEX=lex.yy
YAC=parser.tab

FLAGS=-d
ifeq ($(TEST),1)
FLAGS+= -Wcounterexamples
endif

$(OUT):		$(YAC) $(LEX) $(MAIN) 
			gcc -o $(OUT) $(LEX).o $(MAIN).o
%:			%.c
			gcc -c $@.c
$(LEX).c: 	scanner.l
			flex --header-file=$(LEX).h scanner.l
$(YAC).c:	parser.y
			bison parser.y $(FLAGS)
clean:
			find . \( -name '*.o' -o -name '$(LEX).*' -o -name '$(OUT)' -o -name '$(YAC).*' \) -type f -delete