#gcc -Wall -ggdb main.c -I/usr/local/ffmpeg/include -L/usr/local/ffmpeg/lib  -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lm -lz -pthread -o ./build/cffmpeg -D__STDC_CONSTANT_MACROS
all:cffmpeg
cffmpeg:
	gcc -Wall -ggdb main.c -I/usr/local/ffmpeg/include -L/usr/local/ffmpeg/lib  -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lm -lz -pthread -o ./build/cffmpeg -D__STDC_CONSTANT_MACROS
