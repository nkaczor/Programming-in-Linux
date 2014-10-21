#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
int main(int argc, char* argv[])
{
	int i;
	for(i=1; i<argc; i++){
		int file=open(argv[i],O_RDONLY);
		char a;
		int size=0;
		while(read(file,&a,1)>0)
		{
			size++;
		}
		printf("Rozmiar pliku %s to %d bajty \n", argv[i], size);
		close(file);
	}

	return 0;
}

