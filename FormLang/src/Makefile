CC = gcc
CFLAGS = -Wall -g
FLEX = flex
BISON = bison

TARGET = formLang

LEX_SRC = lexer.l
YACC_SRC = parser.y
C_SRC = html_generator.c

LEX_C = lex.yy.c
YACC_C = y.tab.c
YACC_H = y.tab.h
OBJS = $(LEX_C:.c=.o) $(YACC_C:.c=.o) $(C_SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(LEX_C) $(YACC_C) $(C_SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

$(YACC_C) $(YACC_H): $(YACC_SRC)
	$(BISON) -d -y $<

$(LEX_C): $(LEX_SRC) $(YACC_H)
	$(FLEX) $<

clean:
	rm -f $(TARGET) $(LEX_C) $(YACC_C) $(YACC_H) *.o

.PHONY: all clean
