#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 int main() 
 {
 	int pid = fork();
 	if (pid == 0) {
 		printf("I am child after fork(), launching ps -ef\n");
 		char *args[]= { "/bin/ps", "-ef" , NULL};
 		execvp("/bin/ps", args);
 		printf("finish exec ps -ef\n");
 	}
 	else printf("I am parent after fork(), child is %d\n", pid);
 	
  pid = fork();
 	if (pid == 0) {
 		printf("I am child after fork(), launching free -h\n");
 		char *args[]= { "free", "-h" , NULL};
 		execvp("free", args);
 		printf("finish  free -h\n");
 	}
 	else printf("I am parent after fork(), child is %d\n", pid);
 	return 0;
 } 
