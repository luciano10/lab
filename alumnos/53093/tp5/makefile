LDLBIS=-pthread
GETS=server
FLAGS= -Wall -g -pthread -lrt
CC= gcc
TARGETS=server

server: server.c main.c conexion.c archivo_config.c puerto.c puerto.h
	$(CC) $(FLAGS) $(LDLBIS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o *~
