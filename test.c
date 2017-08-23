#include <stdio.h>
#include "transcoding.h"

int main(int argc, char **argv)
{
	char *input_file = "/mnt/hgfs/web/c++/ffmpeg-transocding/build/input.mp4";
	char *output_file = "/mnt/hgfs/web/c++/ffmpeg-transocding/build/output.mp4";
    //av_log_set_level(AV_LOG_DEBUG);
	run_transcoding(argc, argv, input_file, output_file);
	printf("test start ...\n");
    return 0;
}
