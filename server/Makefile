CFLAGS+=-I../include/ 
CFLAGS+=-lsqlite3
all:server
server:server_init.o sqlite_func.o close_fd.o server_func.o server_main.o
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm *.o server -rf