main: src/main.c src/vm.c src/vm.h src/parser.h
	gcc -o bin/main.o src/main.c src/vm.c src/parser.c
