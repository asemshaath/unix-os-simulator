CFLAGS= -Wall -Werror -fstack-protector-all -ansi -pedantic-errors -g
CC = gcc

all: public01.x public02.x public03.x public04.x public05.x public06.x public07.x public08.x public09.x public10.x public11.x public12.x public13.x public14.x public15.x


public01.x: ournix.o public01.o
	$(CC) $(CFLAGS) ournix.o public01.o -o public01.x

public01.o: public01.c ournix.h ournix-datastructure.h
	$(CC) -c public01.c

public02.x: ournix.o public02.o
	$(CC) $(CFLAGS) ournix.o public02.o -o public02.x

public02.o: public02.c ournix.h ournix-datastructure.h
	$(CC) -c public02.c

public03.x: ournix.o public03.o
	$(CC) $(CFLAGS) ournix.o public03.o -o public03.x

public03.o: public03.c ournix.h ournix-datastructure.h
	$(CC) -c public03.c

public04.x: ournix.o public04.o
	$(CC) $(CFLAGS) ournix.o public04.o -o public04.x

public04.o: public04.c ournix.h ournix-datastructure.h
	$(CC) -c public04.c

public04.x: ournix.o public04.o
	$(CC) $(CFLAGS) ournix.o public04.o -o public04.x

public04.o: public04.c ournix.h ournix-datastructure.h
	$(CC) -c public04.c

public05.x: ournix.o public05.o
	$(CC) $(CFLAGS) ournix.o public05.o -o public05.x

public05.o: public05.c ournix.h ournix-datastructure.h
	$(CC) -c public05.c


public06.x: ournix.o public06.o
	$(CC) $(CFLAGS) ournix.o public06.o -o public06.x

public06.o: public06.c ournix.h ournix-datastructure.h
	$(CC) -c public06.c


public07.x: ournix.o public07.o
	$(CC) $(CFLAGS) ournix.o public07.o -o public07.x

public07.o: public07.c ournix.h ournix-datastructure.h
	$(CC) -c public07.c


public08.x: ournix.o public08.o
	$(CC) $(CFLAGS) ournix.o public08.o -o public08.x

public08.o: public08.c ournix.h ournix-datastructure.h
	$(CC) -c public08.c


public09.x: ournix.o public09.o
	$(CC) $(CFLAGS) ournix.o public09.o -o public09.x

public09.o: public09.c ournix.h ournix-datastructure.h
	$(CC) -c public09.c

public10.x: ournix.o public10.o driver.o
	$(CC) $(CFLAGS) ournix.o public10.o driver.o -o public10.x

public10.o: public10.c ournix.h ournix-datastructure.h driver.h
	$(CC) -c public10.c

public11.x: ournix.o public11.o
	$(CC) $(CFLAGS) ournix.o public11.o -o public11.x

public11.o: public11.c ournix.h ournix-datastructure.h
	$(CC) -c public11.c


public12.x: ournix.o public12.o
	$(CC) $(CFLAGS) ournix.o public12.o -o public12.x

public12.o: public12.c ournix.h ournix-datastructure.h
	$(CC) -c public12.c


public13.x: ournix.o public13.o
	$(CC) $(CFLAGS) ournix.o public13.o -o public13.x

public13.o: public13.c ournix.h ournix-datastructure.h
	$(CC) -c public13.c


public14.x: ournix.o public14.o memory-checking.o
	$(CC) $(CFLAGS) ournix.o public14.o memory-checking.o -o public14.x

public14.o: public14.c ournix.h ournix-datastructure.h memory-checking.h
	$(CC) -c public14.c


public15.x: ournix.o public15.o memory-checking.o
	$(CC) $(CFLAGS) ournix.o public15.o memory-checking.o -o public15.x

public15.o: public15.c ournix.h ournix-datastructure.h memory-checking.h
	$(CC) -c public15.c

	
ournix.o: ournix.c ournix.h ournix-datastructure.h
	$(CC) -c ournix.c

	
test:
	public01.x | diff - public01.output
	public02.x | diff - public02.output
	public03.x | diff - public03.output
	public04.x | diff - public04.output
	public05.x | diff - public05.output
	public06.x | diff - public06.output
	public07.x | diff - public07.output
	public08.x | diff - public08.output
	public09.x | diff - public09.output
	public10.x < public10.input | diff - public10.output
	public11.x | diff - public11.output
	public12.x | diff - public12.output
	public13.x | diff - public13.output
	public14.x | diff - public14.output
	public15.x | diff - public15.output

clean: 
	rm -f *.x
	rm public01.o
	rm public02.o
	rm public03.o
	rm public04.o
	rm public05.o
	rm public06.o
	rm public07.o
	rm public08.o
	rm public09.o
	rm public10.o
	rm public11.o
	rm public12.o
	rm public13.o
	rm public14.o
	rm public15.o
