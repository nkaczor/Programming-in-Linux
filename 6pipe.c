#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
	char buf[200];
	int tab[2];
	int tab2[2];
	int tab3[2];
	int tab4[2];
	int tab5[2];
	pipe(tab);
	pipe(tab2);
	pipe(tab3);
	pipe(tab4);
	pipe(tab5);

	if (fork() == 0)
	{
		if (fork() == 0)
		{

			if (fork() == 0)
			{
				close(tab[0]);
				close(tab2[0]);
				close(tab2[1]);
				close(tab3[0]);
				close(tab3[1]);
				close(tab4[0]);
				close(tab4[1]);
				close(tab5[0]);
				close(tab5[1]);
				dup2(tab[1], 1);
				execlp("ps", "ps", "-ef", NULL);
			}
			else{
				close(tab2[0]);
				close(tab[1]);

				close(tab3[0]);
				close(tab3[1]);
				close(tab4[0]);
				close(tab4[1]);
				close(tab5[0]);
				close(tab5[1]);

				dup2(tab[0], 0);
				dup2(tab2[1], 1);

				execlp("tr", "tr", "-s","' '",":", NULL);
			}

		}
		else
		{
			if (fork() == 0)
			{
				close(tab[0]);
				close(tab[1]);
				close(tab2[1]);
				close(tab3[0]);
				close(tab4[0]);
				close(tab4[1]);
				close(tab5[0]);
				close(tab5[1]);
				dup2(tab2[0], 0);
				dup2(tab3[1], 1);
				execlp("cut", "cut", "-d:","-f1", NULL);
			}
			else{
				close(tab[0]);
				close(tab[1]);
				close(tab2[1]);
				close(tab2[0]);
				close(tab4[0]);
				close(tab3[1]);
				close(tab5[0]);
				close(tab5[1]);
				dup2(tab3[0], 0);
				dup2(tab4[1], 1);
				execlp("sort", "sort",NULL);
			}}
	}
	else
	{
		if (fork() == 0)
		{
			close(tab[0]);
			close(tab[1]);
			close(tab2[1]);
			close(tab2[0]);
			close(tab3[0]);
			close(tab3[1]);
			close(tab5[0]);
			close(tab4[1]);
			dup2(tab4[0], 0);
			dup2(tab5[1], 1);
			execlp("uniq", "uniq","-c",NULL);
		}
		else{
			close(tab[0]);
			close(tab[1]);
			close(tab2[1]);
			close(tab2[0]);
			close(tab3[0]);
			close(tab3[1]);
			close(tab5[1]);
			close(tab4[0]);
			close(tab4[1]);
			dup2(tab5[0], 0);
			execlp("sort", "sort","-n", NULL);
		}
	}
	return 0;
}
