#ifndef CMDUTILS_H
#define CMDUTILS_H

#include <stdint.h>
#include <libavcodec/avcodec.h>
#include <libavfilter/avfilter.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/avstring.h>
#include <libavutil/eval.h>
#include <libavutil/opt.h>

typedef struct SpecifierOpt {
    char *specifier;    /**< stream/chapter/program/... specifier */
    union {
        uint8_t *str;
        int        i;
        int64_t  i64;
        float      f;
        double   dbl;
    } u;
} SpecifierOpt;

typedef struct OptionDef {
    const char *name;
    int flags;
#define HAS_ARG    0x0001
#define OPT_BOOL   0x0002
#define OPT_EXPERT 0x0004
#define OPT_STRING 0x0008
#define OPT_VIDEO  0x0010
#define OPT_AUDIO  0x0020
#define OPT_INT    0x0080
#define OPT_FLOAT  0x0100
#define OPT_SUBTITLE 0x0200
#define OPT_INT64  0x0400
#define OPT_EXIT   0x0800
#define OPT_DATA   0x1000
#define OPT_PERFILE  0x2000     /* the option is per-file (currently ffmpeg-only).
                                   implied by OPT_OFFSET or OPT_SPEC */
#define OPT_OFFSET 0x4000       /* option is specified as an offset in a passed optctx */
#define OPT_SPEC   0x8000       /* option is to be stored in an array of SpecifierOpt.
                                   Implies OPT_OFFSET. Next element after the offset is
                                   an int containing element count in the array. */
#define OPT_TIME  0x10000
#define OPT_DOUBLE 0x20000
#define OPT_INPUT  0x40000
#define OPT_OUTPUT 0x80000
     union {
        void *dst_ptr;
        int (*func_arg)(void *, const char *, const char *);
        size_t off;
    } u;
    const char *help;
    const char *argname;
} OptionDef;

typedef struct Option {
    const OptionDef  *opt;
    const char       *key;
    const char       *val;
} Option;

typedef struct OptionGroupDef {
    /**< group name */
    const char *name;
    /**
     * Option to be used as group separator. Can be NULL for groups which
     * are terminated by a non-option argument (e.g. ffmpeg output files)
     */
    const char *sep;
    /**
     * Option flags that must be set on each option that is
     * applied to this group
     */
    int flags;
} OptionGroupDef;

typedef struct OptionGroup {
    const OptionGroupDef *group_def;
    const char *arg;

    Option *opts;
    int  nb_opts;

    AVDictionary *codec_opts;
    AVDictionary *format_opts;
    AVDictionary *resample_opts;
    AVDictionary *sws_dict;
    AVDictionary *swr_opts;
} OptionGroup;


/**
 * A list of option groups that all have the same group type
 * (e.g. input files or output files)
 */
typedef struct OptionGroupList {
    const OptionGroupDef *group_def;

    OptionGroup *groups;
    int       nb_groups;
} OptionGroupList;

typedef struct OptionParseContext {
    OptionGroup global_opts;

    OptionGroupList *groups;
    int           nb_groups;

    /* parsing state */
    OptionGroup cur_group;
} OptionParseContext;

void *grow_array(void *array, int elem_size, int *size, int new_size);

#define GROW_ARRAY(array, nb_elems) array = grow_array(array, sizeof(*array), &nb_elems, nb_elems + 1)

int split_commandline(OptionParseContext *octx, int argc, char *argv[], const OptionDef *options, const OptionGroupDef *groups, int nb_groups);
static const OptionDef *find_option(const OptionDef *po, const char *name);
static void add_opt(OptionParseContext *octx, const OptionDef *opt, const char *key, const char *val);
static void init_parse_context(OptionParseContext *octx, const OptionGroupDef *groups, int nb_groups);
static void finish_group(OptionParseContext *octx, int group_idx, const char *arg);
static int match_group_separator(const OptionGroupDef *groups, int nb_groups, const char *opt);
static const AVOption *opt_find(void *obj, const char *name, const char *unit, int opt_flags, int search_flags);
static int write_option(void *optctx, const OptionDef *po, const char *opt, const char *arg);
double parse_number_or_die(const char *context, const char *numstr, int type, double min, double max);
int64_t parse_time_or_die(const char *context, const char *timestr, int is_duration);
int opt_default(void *optctx, const char *opt, const char *arg);
int parse_optgroup(void *optctx, OptionGroup *g);
int check_stream_specifier(AVFormatContext *s, AVStream *st, const char *spec);
AVDictionary *filter_codec_opts(AVDictionary *opts, enum AVCodecID codec_id, AVFormatContext *s, AVStream *st, AVCodec *codec);
AVDictionary **setup_find_stream_info_opts(AVFormatContext *s, AVDictionary *codec_opts);
int read_yesno(void);
void exit_program(int ret);
void print_error(const char *filename, int err);
void register_exit(void (*cb)(int ret));
void init_opts(void);
void uninit_opts(void);
void uninit_parse_context(OptionParseContext *octx);

#endif