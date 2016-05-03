#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
int main(){
        int pd[2];
        int leido;
        char buff[100];
        pid_t pid;
        if (pipe(pd)<0){
                perror("pipe()"); // si es menor que 0 entra y da la descripcion del eror
                 return -1;
}
pid = fork();
if(pid == 0) {
while(leido=!0){
leido=read(STDOUT_FILENO, buff, sizeof buff);
write(pd[1],buff,leido);
    }
   return 0;
} 
while(leido=!0){  
leido=read (pd[0],buff,sizeof buff);
write(STDOUT_FILENO,buff,leido);
}
return 0;
}


