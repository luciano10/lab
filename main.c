#include "histograma.h"


int main (int argc , char **argv){
	
	int k,hijos;
        int i,n;
        int m=0,r=1;
        int fd[2];
        int valor1;
	int opcion1,opcion2;
	char * op="n";
	char * op2= "o";	
	char * valor;
	int fc1;
	char buffer;
	char*  mem;
        int a=1,c=0,fd1[2];
        int g,z,q,temp;
	int * dato;
	int * auxiliar;
	
	//Abro el archivo y cuento sus bytes
	 printf ("nombre del archivo: %s\n", argv[1]);
        fc1=open(argv[1],O_RDWR, NULL);//funcion open del argunto[1] dando flagsde lectura y escritura   
        while(read (fc1,&buffer,1)>0){
                m++;// aumenta la variable m 
                if(buffer== ' '){ // se fija si el buffer esta vacio
                        r++; // aumenta la variable r
                }
        }
        close(fc1);//cierre del open
        printf("numero de bytes %d\n",m);	
        mem=calloc(m,1);//retorna en un puntero en este caso en memoria 

	//se realiza el trabajo con el -n(numero de hijos) y -o
	while(1){
	
		opcion1=getopt(argc,argv,op);//analiza argu de la linea de ordenes
		opcion2=getopt(argc, argv, op2);
		if(opcion1==-1)//si no hay caracter de opcion
			break;
		if (opcion2== -1)
			break;
		switch(opcion1){
			case 'n'://numero de hijos
				n=atoi(argv[3]);// transforma la cadena en int 
				printf ("Numero de hijos: %d\n", n);
			break;
			default :
				printf("Error\n");
				exit (0);
			break;	
		} 
		switch(opcion2){
			case 'o':// esto es para ver el orden
				valor =  argv[5];
				if(!strcmp(valor,"a"))//compara lo que ingreso con a
					valor1=1;	
				if (!strcmp(valor,"d"))
					valor1=0;
				break;
			default :
				printf("Error\n");
				exit (0);
			break;
			
		}

	}
	dato = malloc(sizeof(int )*2);
	auxiliar=calloc(r,2); // retorna al puntero auxiliar
	
        //se pasa a la creacion de los hijos
	hijos=atoi(argv[4]);
	printf("proceso padre %d  %s\n", getpid(), argv[3]);	
	pipe(fd);//definir tuberia
	pipe (fd1);//definir tuberia
	fc1=open(argv[3],O_RDWR,NULL);//funcion open con flag de escritu y lectura
	while(read(fc1,mem,m)>0){
		write (fd[1],mem,m);// se escribe en pipe
	}
	close (fc1);
	for(i=0; i<hijos; i++){//for para crear reiterados hijos
		switch(fork()){	
			case 0 ://hijo
	printf("Soy el de hijo de  %d mi PID es: %d\n",getppid(), getpid());
				close (fd[1]);
				close (fd1[0]);
		     	while(read( fd[0],&buffer,1)>0){
					if(buffer==' '){
						a++;
					}else c++;
						auxiliar[a]=auxiliar[a]+1;
					if(a == r ){ 
						*dato=a;	
						write (fd1[1], dato, 1);
						
						if(valor1==1){
							for(z=0; z<(a-1); z++){
								for (g=z+1; g<a; g++){
									if(auxiliar[g]< auxiliar[z]){
										temp=auxiliar[g];
										auxiliar[g]=auxiliar[z];
										auxiliar[z]=temp;
									}				
								}	
							}
							for (q=0; q<a; q++){
								if (auxiliar[q]==auxiliar[q+1]){
									k++;
								}
								if(auxiliar[q]!=auxiliar[q+1]){
								  if(auxiliar[q]<20 && auxiliar[q]!=0)	
						printf("hay %d palabras con %d caracteres\n", k+1, auxiliar[q]);
									k=0;
									
								}	
							}
						} else if (valor1 ==0){
						
                                                        for(z=0; z<(a-1); z++){
                                                                for (g=z+1; g<a; g++){
                                                                        if(auxiliar[g]>auxiliar[z]){
                                                                                temp=auxiliar[g];
                                                                                auxiliar[g]=auxiliar[z];
                                                                                auxiliar[z]=temp;
                                                                        }
                                                                }
                                                        }
                                                        for (q=0; q<a; q++){
                                                		if (auxiliar[q]==auxiliar[q+1]){
                                                                        k++;
                                                                }
                                                                if(auxiliar[q]!=auxiliar[q+1]){
									if(auxiliar[q]<20 && auxiliar[q]!=0)
                                               printf("hay %d palabras con %d caracteres\n", k+1, auxiliar[q]);
                                                                        k=0;
									
								}
                                                        }
						}
						break;
							
					}

				}
			
					
				exit (0);	
			break;
		}

	}
	close (fd1[1]);
	close (fd[0]);
	read (fd1[0], dato,1);
	printf("La cantidad de palabras contadas son: %i \n",*dato);
	*dato=a;

	sleep(5);
	return 0;
}
