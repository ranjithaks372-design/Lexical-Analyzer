CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = lexical_analyzer

SRC = main.c scanner.c Identifier.c number.c operator.c \
      comment.c Delimiter.c String_literal.c \
      preprocessor.c error.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c lexer.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)