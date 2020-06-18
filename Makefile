mc.o: mc.c
	gcc -c mc.c
	mv mc.o build/

mc: mc.o 
	gcc build/mc.o -o mc

run: mc
	./mc -p hello.c 
