CC := g++
CFLAGS := -Wall -Wextra -std=c++11 -g
TARGET := ./main.exe

.PHONY: all clean main run lex yacc test debug link testscope asm asmc nasm example-code out mytest

all: complier

src/pch.h.gch: src/pch.h
	g++ -x c++-header -o src/pch.h.gch -c src/pch.h

lex:
	flex -o"src\lexer.cpp" src\lexer.l

yacc:
	bison -o"src\parser.cpp" --defines=src\parser.h src\parser.y

main: src/pch.h.gch
	$(CC) $(CFLAGS) src\\*.cpp -o $(TARGET)

complier: lex yacc main

run: complier

clean:
	del /s "src\lexer.cpp" "src\parser.cpp" "src\parser.h" "src\pch.h.gch" "$(TARGET)" "*.o" ".\bin\*"
	del /s "src\*.output"
	del /s test\*\*.out test\*\*.output
