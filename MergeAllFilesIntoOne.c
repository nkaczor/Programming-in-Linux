#include <stdio.h>
#include <fcntl.h>
#define MAX 1000
int main(int argc, char *argv[])
{
	int toFile = creat(argv[argc-1], 0640);
	int i;
	int fromFile;
	char buf[MAX];
	for (i = 1; i < argc-1; i++)
	{
		fromFile = open(argv[i], O_RDONLY);
		lseek(fromFile, 0, SEEK_SET);
		int lbajt;
		while ((lbajt = read(fromFile, buf, MAX)) > 0)
		{
			write(toFile, buf, lbajt);
		}
	}

	close(toFile);
	return 0;
}






