#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


#include "ClPort.h"
#include "ClHistory.h"
#include "ClEditLine.h"

int main(int argc, char *argv[])
{
	char Heap[4096];
	char szBuffer[1024];
	cl_mem_init(Heap, sizeof(Heap), 100);
	cl_history_init();

	/*
	 * Switch from canonical to raw mode
	 */
	struct termios saved, raw;
	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &raw);
	cfmakeraw(&raw);
	raw.c_oflag |= OPOST;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);


	/*
	 * Enter main loop. To exit type: 'exit' and hit enter.
	 */
	while (1) {
		if (cl_editline("# ", szBuffer, sizeof(szBuffer), 5) > 0) {
			if (strcmp(szBuffer, "exit") == 0)
				goto exit;
			printf("\r\nYou wrote: %s", szBuffer);
		}
		printf("\r\n");
	}

exit:
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	printf("\r\n");
	return 0;
}
