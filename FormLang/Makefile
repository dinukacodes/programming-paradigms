CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lfl

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(SRC_DIR)/html_generator.c $(SRC_DIR)/parser.tab.c $(SRC_DIR)/lex.yy.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = $(BIN_DIR)/formLang

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/lex.yy.c: $(SRC_DIR)/lexer.l $(SRC_DIR)/parser.tab.h
	flex -o $@ $<

$(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	bison -d -o $(SRC_DIR)/parser.tab.c $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(SRC_DIR)/lex.yy.c $(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h 