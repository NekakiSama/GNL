#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
int main (void)
{
	//char *line1;
	char *line2;
	int fd1 = open("../test.txt", O_RDONLY);
	int	fd2 = open("../test2.txt", O_RDONLY);
	//while (get_next_line(fd, &line) > 0)
	while ( get_next_line(fd1, &line1) > 0 || get_next_line(fd2, &line2) > 0)
	{
		//printf("exit line1 = %s\n", line1);
		printf("exit line2 = %s\n", line2);
	}
	close(fd1);
	close(fd2);
	return (0);
}*/
#include "get_next_line.h"
int main(int ac, char **av)
{
	int fd;
	int ret;
	int i;
	char *line;
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%d -> [%s]\n", i, line);
		free(line);
		i++;
	}
	printf("RET: %d\n", ret);
//	free(line);
	close(fd);
	system("leaks a.out");
	return (0);
}
