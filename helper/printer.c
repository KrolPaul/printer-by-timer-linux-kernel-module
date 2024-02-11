#include <sys/file.h>

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	if (argc < 3){
		printf("Too few command line arguments\n");
		return 1;
	}
	
	int fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == -1){
		perror("Open file error: ");
		return 2;
	}
		
	const ssize_t write_bytes = strlen(argv[2]);
	flock(fd, LOCK_EX);
	ssize_t written_bytes = write(fd, argv[2], write_bytes);
	flock(fd, LOCK_UN);
	close(fd);
	
	if (written_bytes != write_bytes){
		perror("Write to file error: ");
		return 3;
	}
	return 0;
}
