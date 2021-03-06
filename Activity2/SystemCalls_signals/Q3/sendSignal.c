// Write a program to send specific signal to a target process (with given id, like kill command)

#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
// function declaration 
void sighup(); 
void sigint(); 
void sigquit(); 
  
// driver code 
void main() 
{ 
    int ret; 
  
    /* get child process */
    if ((ret = fork()) < 0) { 
        perror("fork"); 
        exit(1); 
    } 
  
    if (ret == 0) { /* child */
        signal(SIGHUP, sighup); 
        signal(SIGINT, sigint); 
        signal(SIGQUIT, sigquit); 
        for (;;) 
            ; /* loop for ever */
    } 
  
    else /* parent */
    { /* pid hold id of child */
        printf("\nPARENT: sending SIGHUP\n\n"); 
        kill(ret, SIGHUP); 
  
        sleep(3); /* pause for 3 secs */
        printf("\nPARENT: sending SIGINT\n\n"); 
        kill(ret, SIGINT); 
  
        sleep(3); /* pause for 3 secs */
        printf("\nPARENT: sending SIGQUIT\n\n"); 
        kill(ret, SIGQUIT); 
        sleep(3); 
    } 
} 
  
// sighup() function definition 
void sighup() 
  
{ 
    signal(SIGHUP, sighup); /* reset signal */
    printf("CHILD:  received a SIGHUP\n"); 
} 
  
// sigint() function definition 
void sigint() 
  
{ 
    signal(SIGINT, sigint); /* reset signal */
    printf("CHILD:  received a SIGINT\n"); 
} 
  
// sigquit() function definition 
void sigquit() 
{ 
    printf("Child process is killed!!!\n"); 
    exit(0); 
} 