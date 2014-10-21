#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
int main(int argc, char* argv[])
{
	int file=open(argv[1],O_RDONLY);
	int maxLine=0;
	int curLine=0;
	char a;
	while(read(file,&a,1)>0)
	{
		if(a=='\n'){
			if(curLine>maxLine) maxLine=curLine;
			curLine=0;
		}
		else curLine++;
	}

	printf("Najdluzsza linia %d \n",maxLine);

	return 0;
}

