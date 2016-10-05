LDLBIS=-pthread
GETS=server
FLAGS= -Wall -g -pthread -lrt
CC= gcc
TARGETS=server

server: server.c main.c conexion.c
	$(CC) $(FLAGS) $(LDLBIS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o *~
