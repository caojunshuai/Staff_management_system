CFLAGS+=-I../include/ 
all:client
client:client_main.o client_func.o operat_func.o staffinfo_io.o
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm *.o client -rf