CC = cc68x

OBJS = duckdash.o model.o renderer.o raster.o font.o input.o synch.o asynch.o cond.o

duckdash.tos: $(OBJS)
	$(CC) -o duckdash.tos $(OBJS)

duckdash.o: duckdash.c
	$(CC) -c duckdash.c

model.o: model.c
	$(CC) -c model.c

renderer.o: renderer.c
	$(CC) -c renderer.c

raster.o: raster.c
	$(CC) -c raster.c

font.o: font.c
	$(CC) -c font.c

input.o: input.c
	$(CC) -c input.c

synch.o: synch.c
	$(CC) -c synch.c

asynch.o: asynch.c
	$(CC) -c asynch.c

cond.o: cond.c
	$(CC) -c cond.c

clean:
	rm *.o
	rm duckdash.tos