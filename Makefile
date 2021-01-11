OBJS = scanner.o parser.o ast.o interpreter.o            # Ficheiros necessarios para a construção do programa
INTERM = scanner.c parser.c parser.h		           	 # Ficheiros criados atraves do makefile
PROGRAM = interpreter	     				             # Ficheiro target

all: $(PROGRAM)

scanner.c: scanner.flex parser.h			              # Para criar o ficheiro executavel scanner.c necessitamos dos ficheiros scanner.flex, parser.h
	flex -o scanner.c scanner.flex

parser.c parser.h: parser.bison				              # Para criar os ficheiros executaveis parser.c e parse.h necessitamos do ficheiro parser.bison
	bison --defines=parser.h -o parser.c parser.bison

$(PROGRAM): $(OBJS)							              # Para compilar o $(PROGRAM) necessitmos dos ficheiros $(OBJS)
	gcc -o $(PROGRAM) $(OBJS)

clean:										              # Remover os ficheiros $(PROGRAM) e $(INTERM)
	rm -f $(PROGRAM) $(INTERM)

test: $(PROGRAM)							              # Ficheiros teste
	./$(PROGRAM) test.c
