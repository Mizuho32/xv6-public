#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

int main(int argc, char* argv[]){
	printf(1, "Hello, World!\n");

  if (argc == 1){
    printf(2, "Argument Error\n!");
    exit();
  }

  int i = 0;

  char* A = argv[1];
  int fd_A = open(A, O_RDONLY);
  char* B = argv[2];
  int fd_B = open(B, O_WRONLY | O_CREATE);

  struct stat stat_A, stat_B;
  fstat(fd_A, &stat_A);
  fstat(fd_B, &stat_B);

  char *bufA = (char*)malloc(sizeof(char)*stat_A.size);
  char *bufB = (char*)malloc(sizeof(char)*stat_B.size);
  read(fd_A, bufA, stat_A.size);
  read(fd_B, bufB, stat_B.size);

  i = stat_A.size -2;
  int len;

  for(; i > -1; ){
    len = 1;
    for(; bufA[i] != '\n' && i >= 0; i--, len++);
    printf(1, "len:%d i:%d\n", len, i);
    write(fd_B, &bufA[i+1], len);
    i--;
  }

  free(bufA);
  close(fd_A);
  free(bufB);
  close(fd_B);

	exit();
}
