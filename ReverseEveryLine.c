#include <stdio.h>
#include <fcntl.h>

void reverse(char *buff, int n)
{
	int k = n - 1;
	int i;
	char c;
	for (i = 0; i < n / 2; i++)
	{
		c = buff[i];
		buff[i] = buff[k];
		buff[k] = c;
		k--;
	}


}
int main(int argc, char *argv[])
{
	int file = open(argv[1], O_RDWR, 0777);
	char buff[1000];
	char a;
	int i = 0;

	while (read(file, &a, 1) > 0)
	{

		if (a != '\n')
		{
			buff[i] = a;
			i++;
		}
		else
		{
			reverse(buff, i);
			int pos = lseek(file, (off_t) - i - 1, SEEK_CUR);
			write(file, buff, i);
			pos = lseek(file, (off_t) 1, SEEK_CUR);
			i = 0;
		}
	}


	lseek(file, (off_t) - i - 1, SEEK_CUR);
	reverse(buff, i);
	write(file, buff, i);

	close(file);
	return 0;
}
