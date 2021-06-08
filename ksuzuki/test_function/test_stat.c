#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	struct stat sb;

	if (stat(argv[1], &sb) == -1)
	{
		printf("error\n");
		return (1);
	}
	if (S_ISDIR(sb.st_mode))
		printf("is dir\n");
	printf("%d\n", sb.st_mode);
}