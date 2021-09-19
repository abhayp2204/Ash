all:
	gcc ./src/*.c -c

	gcc *.o -o ash
	mkdir -p obj
	mv *.o obj