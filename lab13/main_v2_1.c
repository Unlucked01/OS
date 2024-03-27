#include <stdio.h>
#include <dirent.h>

int main()
{
	fputs("Enter directory: ", stdout);
	char dir[256];
	scanf("%s", dir);

	DIR *dirdes = opendir(dir);
	
	if (dirdes == NULL) {
		perror(NULL);
		return 0;
	} 

	struct dirent *curdir = readdir(dirdes);

	puts("Directory content: ");

	while (curdir != NULL) {
		puts(curdir->d_name);
		curdir = readdir(dirdes);
	}
	
	closedir(dirdes);

	return 0;
}
