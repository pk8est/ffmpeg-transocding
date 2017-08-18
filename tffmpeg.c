#include <stdio.h>
#include "tffmpeg.h"
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

int main(int argc, char **argv)
{
	printf("Start ...\n");
	av_log_set_flags(AV_LOG_SKIP_REPEATED);
	return 0;
}
