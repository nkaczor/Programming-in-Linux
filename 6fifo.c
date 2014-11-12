#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char* argv[])
{
	mkfifo("fifo_1",0644);
	 mkfifo("fifo_2",0644);
	 mkfifo("fifo_3",0644);
	 mkfifo("fifo_4",0644);
	 mkfifo("fifo_5",0644);
	if (fork() == 0)
	{
		if (fork() == 0)
		{

			if (fork() == 0)
			{
				
				int to=open("fifo_1", O_WRONLY);
				dup2(to, 1);
				  execlp("ps", "ps","-ef" ,NULL);
			}
			else{
				
			    int from=open("fifo_1", O_RDONLY);
				int to=open("fifo_2",O_WRONLY);
			    dup2(from, 0);
			    dup2(to,1);
				
				execlp("tr", "tr", "-s","' '",":", NULL);
			}

		}
		else
		{
			if (fork() == 0)
			{
				int from=open("fifo_2", O_RDONLY);
				int to=open("fifo_3",O_WRONLY);
			    dup2(from, 0);
			    dup2(to,1);
				execlp("cut", "cut", "-d:","-f1", NULL);
			}
			else{
				
				int from=open("fifo_3", O_RDONLY);
				int to=open("fifo_4",O_WRONLY);
			    dup2(from, 0);
			    dup2(to,1);
				execlp("sort", "sort",NULL);
			}}
	}
	else
	{
		if (fork() == 0)
		{
			
			int from=open("fifo_4", O_RDONLY);
				int to=open("fifo_5",O_WRONLY);
			    dup2(from, 0);
			    dup2(to,1);
			execlp("uniq", "uniq","-c",NULL);
		}
		else{
			
			int from=open("fifo_5", O_RDONLY);
				
			    dup2(from, 0);
			   
			execlp("sort", "sort","-n", NULL);
		}
	}
	unlink("fifo_1");
	unlink("fifo_2");
	unlink("fifo_3");
	unlink("fifo_4");
	unlink("fifo_5");
	
	return 0;
}
