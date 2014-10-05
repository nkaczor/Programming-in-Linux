/*
 Wejście programu: Copy opcja plik_out plik_in
 Program kopiuje 10 ostatnich linii, slow, znakow (w zaleznosci od wybranej opcji)
 z plik_out do plik_in
 Opcje:
 l - linie
 w - słowa
 c - znaki
 */
#include <stdio.h>
#include <fcntl.h>
int CountCharactersInLines(int file, int *charInLines)
{
	char c;
	int i = 10;
	int count = 0;
	lseek(file, (off_t) - 1 , SEEK_END);
	while (i >= 0 && read(file, &c, 1) > 0)
	{
		printf("%c", c);
		count++;
		if (c == '\n')
		{

			charInLines[i--] = count;
			count = 0;

		}
		lseek(file, (off_t) - 2, SEEK_CUR);

	}
	return 10 - i;
}
int CountCharactersInWords(int file, int *charInWords)
{
	char c;
	int i = 9, count = 0, letters = 0;
	lseek(file, (off_t) - 1, SEEK_END);
	while (i >= 0 && read(file, &c, 1) > 0)
	{
		count++;
		if (letters > 0 && (c < 33 || c > 126))
		{
			charInWords[i--] = count;
			count = 0;
			letters = 0;
		}
		else letters++;
		lseek(file, (off_t) - 2, SEEK_CUR);
	}
	return 9 - i; //liczba linii, ktore zostaly policzone
}
void CopyLast10Lines(int fromFile, int toFile)
{
	int charInLines[11];
	char buff[1000];
	int line = CountCharactersInLines(fromFile, charInLines);

	int i, sum = 0;
	for (i = 0; i < line; i++) sum += charInLines[i];
	lseek(fromFile, (off_t) - sum + 1, SEEK_END);
	for (i = 0; i < line; i++)
	{
		int size = read(fromFile, buff, charInLines[i]);
		write(toFile, buff, size);
	}

}
void CopyLast10Chars(int fromFile, int toFile)
{
	char buff[11];
	lseek(fromFile, (off_t) - 10, SEEK_END);
	int size = read(fromFile, buff, 10);
	write(toFile, buff, size);
}
void CopyLast10Words(int fromFile, int toFile)
{
	char buff[1000];
	int charInWords[11];
	int words = CountCharactersInWords(fromFile, charInWords);
	int i, sum = 0;
	for (i = 0; i < words; i++) sum += charInWords[i];
	lseek(fromFile, (off_t) - sum + 1, SEEK_END);
	for (i = 0; i < words; i++)
	{
		int size = read(fromFile, buff, charInWords[i]);
		write(toFile, buff, size);
	}
}
int main(int argc, char* argv[])
{
	int fromFile = open(argv[2], O_RDONLY);
	int toFile = creat(argv[3], 0640);
	if (argv[1][0] == 'l') CopyLast10Lines(fromFile, toFile);
	else if (argv[1][0] == 'c') CopyLast10Chars(fromFile, toFile);
	else if (argv[1][0] == 'w') CopyLast10Words(fromFile, toFile);
	close(fromFile);
	close(toFile);

	return 0;
}
