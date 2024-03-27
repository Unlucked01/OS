#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

void formfile(int fd)
{
	static const char student[] =
		"Sokolova Anna Stepanovna 3\n"
		"Kozlov Semen Nikolaevich 5\n"
		"Glushkova Elina Savvichna 4\n"
		"Ushakova Sofia Adamovna 2\n"
		"Simonov David Lyvovich 3\n"
		"Lyvov Timofei Lyvovich 5\n"
		"Knyazev Viktor Platonovich 4\n"
		"Bogdanov Mikhail Matveevich 5\n"
		"Tikhohnov Miron Georgievich 4\n"
		"Zakharova Anna Ilyinichna 5\n"
        "Bobkov Maxim Igorevich 5\n";

	write(fd, student, sizeof(student));
	lseek(fd, 0, SEEK_SET);
}

void filterfile(int from, int to)
{
	char buf[1024];
	read(from, buf, sizeof(buf));

	char fives[1024] = "";

	char* tok = strtok(buf, "\n");

	while (tok != NULL) {
		if (tok[strlen(tok) - 1] == '5') {
			strcat(fives, tok);
			strcat(fives, "\n");
		}

		tok = strtok(NULL, "\n");
	}

	write(to, fives, sizeof(fives));
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int from = open("marks.txt", O_RDWR | O_CREAT, 0644);
	int to = open("fives.txt", O_WRONLY | O_CREAT, 0644);

	formfile(from);
	filterfile(from, to);

	close(from);
	close(to);

	return 0;
}
