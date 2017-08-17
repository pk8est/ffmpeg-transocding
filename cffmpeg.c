#include <stdio.h>
#include "trans.h"

int main(int argc, char *argv[])
{
	int ret;
	char *input_file = "/mnt/hgfs/web/c++/ffmpeg-transocding/build/input.mp4";
	char *output_path = "/mnt/hgfs/web/c++/ffmpeg-transocding/build";
	printf("Hello!\n");
	ret = CreateTransTask(input_file, output_path);
	return 0;
}
