#ifndef FFMPEG_OPT_H
#define FFMPEG_OPT_H

//static int open_files(OptionGroupList *l, const char *inout, int (*open_file)(OptionsContext*, const char*));
int ffmpeg_parse_options(int argc, char **argv);

#endif