#ifndef COMMON_H_
#define COMMON_H_

extern char *optarg;
extern int optind;

int getopt (int argc, char *const argv[], const char *optstring);

#endif
