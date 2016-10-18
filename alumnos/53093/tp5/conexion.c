#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<signal.h>
#include<fcntl.h>
#include <pthread.h>
#define CONNMAX 1000
#define BYTES 1024
char *ROOT;
int listenfd, clients[CONNMAX];

//conexion del cliente
void respond(int n)
{
    char mesg[99999], *reqline[3], data_to_send[BYTES], path[99999];
    int rcvd, fd, bytes_read;

    memset( (void*)mesg, (int)'\0', 99999 );

    rcvd=recv(clients[n], mesg, 99999, 0);

    if (rcvd<0)    // recibir error
        fprintf(stderr,("recv() error\n"));
    else if (rcvd==0)    // recibe  socket cerrado
        fprintf(stderr,"Client disconnected upexpectedly.\n");
    else    // mensaje recibido
    {
        printf("%s", mesg);
        reqline[0] = strtok (mesg, " \t\n");
        if ( strncmp(reqline[0], "GET\0", 4)==0 )
        {
            reqline[1] = strtok (NULL, " \t");
            reqline[2] = strtok (NULL, " \t\n");
            if ( strncmp( reqline[2], "HTTP/1.1", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 )
            {
                write(clients[n], "HTTP/1.1 400 Bad Request\n", 25);
            }
            else
            {
                if ( strncmp(reqline[1], "/\0", 2)==0 )
                    reqline[1] = "/index.html";        //sino se especifica un archivo index.html se abrira por defecto

                strcpy(path, ROOT);
                strcpy(&path[strlen(ROOT)], reqline[1]);
                printf("file: %s\n", path);

                if ( (fd=open(path, O_RDONLY))!=-1 )    //archivo encontrado
                {
                    send(clients[n], "HTTP/1.1 200 OK\n\n", 17, 0);
                    while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
                        write (clients[n], data_to_send, bytes_read);
                }
                else    write(clients[n], "HTTP/1.1 404 Not Found\n", 23); //archivo no encontrado
            }
        }
    }

    //cerrar sockect
    shutdown (clients[n], SHUT_RDWR);// no se puede enviar operaciones 
    close(clients[n]);
    clients[n]=-1;
}
