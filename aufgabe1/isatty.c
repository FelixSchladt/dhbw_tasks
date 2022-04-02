
#include <stdlib.h>	/* needed for exit() */
#include <unistd.h>	/* needed for isatty() */
#include <stdio.h>	/* needed for printf() */

int
main(int argc, char **argv)
{
	if (isatty(0)) {
		printf("the standard input is from a terminal\n");
    } else {
        char buf[128];
        while (read(STDIN_FILENO, buf, 10) > 0) {
            printf("%s", buf);
        }
		printf("the standard input is NOT from a terminal\n");
    }
	if (isatty(1))
		printf("the standard output is to a terminal\n");
	else
		printf("the standard output is NOT to a terminal\n");
	exit(0);
}
