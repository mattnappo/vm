main: src/main.c src/vm.c src/vm.h src/parser.h
	mkdir -p bin/
	gcc -o bin/vm.o src/main.c src/vm.c src/parser.c
compact: src/compact_vm.c
	mkdir -p bin/
	gcc -o bin/vm.o src/compact_vm.c
clean:
	rm -rf bin/
