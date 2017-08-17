#include <stdio.h>
#include "trans.h"

int main(int argc, char *argv[])
{
	int ret;
	char *input_file = "/mnt/hgfs/web/c++/ffmpeg-transocding/build/input.mp4";
	char *output_file = "/mnt/hgfs/web/c++/ffmpeg-transocding/build/output.mp4";
	char *output_path = "/mnt/hgfs/web/c++/ffmpeg-transocding/build";
//	ret = CreateTransTask(input_file, output_path);
	ret = create_trans_task(input_file, output_file);
	printf("Hello!\n");
	return 0;
}
