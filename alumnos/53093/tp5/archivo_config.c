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

#define CONNMAX 1000
#define BYTES 1024
char *ROOT;
int listenfd, clients[CONNMAX];
 void getIP(int tipo, char * IP){
	FILE *tmpIP;
	char dIP[20];
	char dIP2[20];
	int i,j;
	switch(tipo){
		case 0:
			system("ifconfig lo | grep inet > tmp");
			break;
		case 1:
			system("ifconfig wlan | grep inet > tmp");
			break;
		case 2:
			system("ifconfig eth | grep inet > tmp");
			break;

	
	}//End switch
	j = 0;
	tmpIP = fopen("tmp","r");
	fscanf(tmpIP,"%s %s",dIP,dIP);
	for(i = 5;i<20;i++){
		IP[j] = dIP[i];	
		j++;		
	}
}//End getIP 
