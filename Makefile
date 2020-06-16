mc.o: mc.c
	gcc -c mc.c

mc: mc.o 
	gcc mc.o -o mc

run: mc
	./mc
