#include "stdlib.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
	int file = open(argv[1], O_RDWR);
	char a;
	while (read(file, &a, 1) > 0)
	{
		if (a >= 97 && a <= 122)
		{
			lseek(file, (off_t) - 1, SEEK_CUR);
			a=a-32;
			write(file, &a, 1);
		}
	}
	close(file);


	return 0;
}
