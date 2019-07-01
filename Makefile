main: src/main.c src/vm.c src/vm.h src/parser.h
	mkdir -p bin/
	gcc -o bin/main.o src/main.c src/vm.c src/parser.c
clean:
	rm -rf bin/
