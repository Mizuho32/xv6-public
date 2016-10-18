#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

int main(int argc, char* argv[]){
	printf(1, "Hello, World!\n!");

  if (argc == 1){
    printf(2, "Argument Error\n!");
    exit();
  }

  int i = 0;

  char* A = argv[1];
  int fd_A = open(A, O_RDONLY);
  char* B = argv[2];
  int fd_B = open(B, O_RDONLY);

  struct stat stat_A, stat_B;
  fstat(fd_A, &stat_A);
  fstat(fd_B, &stat_B);
  if (stat_A.size != stat_B.size) {
   printf(2, "%s and %s differ\n", A, B); 
   exit();
  }

  char *bufA = (char*)malloc(sizeof(char)*stat_A.size);
  char *bufB = (char*)malloc(sizeof(char)*stat_B.size);
  read(fd_A, bufA, stat_A.size);
  read(fd_B, bufB, stat_B.size);

  for(i = 0; i < stat_A.size;i++){
    if (bufA[i] != bufB[i]) {
     printf(2, "%s and %s differ\n", A, B); 
     exit();
    }
  }

  free(bufA);
  close(fd_A);
  free(bufB);
  close(fd_B);
  printf(1, "OK\n");

	exit();
}
