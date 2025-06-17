#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>

#define BUFSIZE 100

int main(){
    
    char buf1[] = "Child process 1 is sending a message!\n";
    char buf2[] = "Child process 2 is sending a message! ";
    char buffout[100] = {" "};
    pid_t childpid1, childpid2;
    int fd[2];
    if (pipe(fd) == -1){
        perror("Failed to create the pipe");
        return 1;
    }

    if((childpid1 = fork()) < 0){
        perror("fork");
    }else if (childpid1 == 0){/* child 1 code */
        close(fd[0]);
        int n;
        n = write(fd[1], buf1, strlen(buf1));  
        printf("child 1 write successfully, n is %d\n", n);
        exit(0);
    }

    waitpid(childpid1, NULL, 0);

    if((childpid2 = fork()) < 0){
        perror("fork");
    }else if (childpid2 == 0){/* child 2 code */
        close(fd[0]);
        int n;
        n = write(fd[1], buf2, strlen(buf2));
        printf("child 2 write successfully, n is %d\n", n);
        exit(0);
    }
    
    waitpid(childpid2, NULL, 0);       
    close(fd[1]);
    read(fd[0], buffout, sizeof(buf1)+sizeof(buf2));
    printf("%s\n",  buffout);
    return 0;
}
