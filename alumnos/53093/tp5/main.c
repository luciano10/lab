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
void error(char *);
void startServer(char *);
void respond(int);
void getIP(int tipo, char * IP);
int main(int argc, char* argv[])
{
       int sd;
    int *sdc;
	int sd_conn;
      pthread_t p_thread[3000];
    //int thr_id,i=0;    
    struct sockaddr_in clientaddr;
    socklen_t addrlen;
    char c;    
   pthread_t tid1;
    pthread_attr_t atributo;
    pthread_attr_init(&atributo);
    pthread_attr_setdetachstate(&atributo, PTHREAD_CREATE_DETACHED);
    
    //valores preterminado del puerto =10000
    char PORT[6];
    ROOT = getenv("PWD");
    strcpy(PORT,"10000");

    int slot=0;

    //analisis de los argumentos de linea de comando
    while ((c = getopt (argc, argv, "p:r:")) != -1)
        switch (c)
        {
            case 'r':
                ROOT = malloc(strlen(optarg));
                strcpy(ROOT,optarg);
                break;
            case 'p':
                strcpy(PORT,optarg);
                break;
            case '?':
                fprintf(stderr,"argumentos erroneos!!!\n");
                exit(1);
            default:
                exit(1);
        }
    
    printf("Servidor comenzo en el puerto  %s%s%s con directorio  %s%s%s\n","\033[92m",PORT,"\033[0m","\033[92m",ROOT,"\033[0m");
    //configuracion de los elementos a -1 : significa que el cliente no esta conectado  
    int i;
    for (i=0; i<CONNMAX; i++)
        clients[i]=-1;
    startServer(PORT);
           // acepta conexiones
    while (1)
    {
          sdc=malloc(sizeof (int));
         *sdc=sd_conn;

        addrlen = sizeof(clientaddr);
   clients[slot] = accept (listenfd, (struct sockaddr *) &clientaddr, &addrlen);

        if (clients[slot]<0)
            error("accept() error");
        else
        {
  //  thr_id = pthread_create(&p_thread[i++],NULL,respond,(void*)&new_fd);
       // creo el hilo 
         if ((pthread_create(&tid1,&atributo,&respond,(void *)sdc))!=0){
                    respond(slot);
        		exit(0);
        		
    			}				
			             } 
			
 
        //while (clients[slot]!=-1) slot = (slot+1)%CONNMAX;

    
  }   
    return 0;
}

