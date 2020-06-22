mc.o: mc.c
	gcc -c mc.c
	mv mc.o build/

mc: mc.o 
	gcc build/mc.o -o mc

install: mc 
	cp mc /usr/local/bin

run: mc
	./mc -p hello.c 
