#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
	char buf[200];
	int tab[2];
	int tab2[2];
	pipe(tab);
	pipe(tab2);


	if (fork() == 0)
	{
		if (fork() == 0)
		{
			close(tab[0]);
			close(tab2[0]);
			close(tab2[1]);
			dup2(tab[1], 1);
			execlp("ls", "ls", "-l", NULL);

		}
		else
		{
			close(tab[1]);
			close(tab2[0]);
			dup2(tab[0], 0);
			dup2(tab2[1], 1);
			execlp("grep", "grep", "^d", NULL);


		}


	}
	else
	{
		close(tab[1]);
		close(tab[0]);
		close(tab2[1]);
		dup2(tab2[0], 0);
		execlp("more", "more",  NULL);


	}

	return 0;
}






