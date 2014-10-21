#include "stdlib.h"
#include "fcntl.h"
#include "stdio.h"
int main(int argc, char * argv[])
{
	int file;
	if (argc < 1) file = 0;
	else file = open(argv[1], O_RDONLY);
	char a;
	int counter=0;
	int ifWhiteSpaces=1;
	while(read(file,&a, 1)>0){
		if(a<33) {
		if(ifWhiteSpaces==0)counter++; 
			ifWhiteSpaces=1;
		}
		else  ifWhiteSpaces=0; 
	
	
	}
	printf("Liczba slow w pliku wynosi: %d ", counter++);
	return 0;
}

