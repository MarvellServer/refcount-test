/*
 * simple open/read/close test
 *
 * usage: ./otest [count] [str]
 *
 * Wait for the file /tmp/o-test to be created, then open, read and close
 * /tmp/x/o-file 'count' times. 'str' is just for tagging output
 *
 * compile with: cc -O2 -Wall -o ./otest otest.c 
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>

#define SYNCFILE	"/tmp/o-test"
#define RDFILE		"/tmp/x/o-file"

int main(int argc, char *argv[])
{
	struct timeval t1, t2;
	long i, t, n, fd;
	const char *tag;
	char buf[64];

	t = (argc >= 2)?  atoi(argv[1]) : 0;
	n = t? t: 1000000;
	tag = (argc == 3)?  argv[2] : "-";

	while (1) {
		fd = open(SYNCFILE, O_RDONLY);
		if (fd >= 0)
			break;
	}
	close(fd);

	gettimeofday(&t1, NULL);
	for (i = 0; i < n; i++) {
		fd = open(RDFILE, O_RDONLY);
		if (fd < 0)
			goto fail;
		t = read(fd, buf, sizeof(buf));
		if (t < 0)
			goto fail;
		close(fd);
	}
	gettimeofday(&t2, NULL);

	printf("%s %ld open/read/close in %.3fus\n", tag, n,
			((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))/1.0e6);
	return 0;

fail:
	printf("Failed with %d: %s!\n", errno, strerror(errno));
	return 1;
}
