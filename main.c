#include <stdio.h>
#include <libavformat/avformat.h>

int main(int argc, char *argv[])
{
	av_register_all();
	printf("Hello world!\n");
	return 0;
}
