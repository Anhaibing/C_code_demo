#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <fcntl.h>

#include "debug.h"
#include "common.h"
#include "timefunc.h"
#include "slog.h"

#define VERSION_STR "1.1_devel"

static void show_version (void) {
	fprintf (stderr,
			"hostapd v" VERSION_STR "\n"
			"User space daemon for IEEE 802.11 AP management,\n"
			"IEEE 802.1X/WPA/WPA2/EAP/RADIUS Authenticator\n"
			"Copyright (c) 2002-2015, Jouni Malinen <j@w1.fi> "
			"and contributors\n");
}

static void usage (void) {
	show_version ();
	fprintf (stderr,
			"\n"
			"usage: hostapd [-hdBKtv] [-P <PID file>] [-e <entropy file>] "
			"\\\n"
			"         [-g <global ctrl_iface>] [-G <group>] \\\n"
			"         <configuration file(s)>\n"
			"\n"
			"options:\n"
			"   -h   show this usage\n"
			"   -d   show more debug messages (-dd for even more)\n"
			"   -B   run daemon in the background\n"
			"   -e   entropy file\n"
			"   -g   global control interface path\n"
			"   -G   group for control interfaces\n"
			"   -P   PID file\n"
			"   -K   include key data in debug messages\n"
#ifdef CONFIG_DEBUG_FILE
			"   -f   log output to debug file instead of stdout\n"
#endif /* CONFIG_DEBUG_FILE */
#ifdef CONFIG_DEBUG_LINUX_TRACING
			"   -T = record to Linux tracing in addition to logging\n"
			"        (records all messages regardless of debug verbosity)\n"
#endif /* CONFIG_DEBUG_LINUX_TRACING */
			"   -t   include timestamps in some debug messages\n"
			"   -v   show hostapd version\n");
	exit (1);
}

int main (int argc, char * argv[]) {

	int c, debug = 0;
	for (;;) {
		c = getopt (argc, argv, "b:d:f:hKP:Ttu:g:G:v::");
		if (c < 0) break;
		switch (c) {
			case 'h':
				usage();
				break;
#ifdef CONFIG_DEBUG_FILE
			case 'd':
				log_init(optarg, NULL);
				break;
			case 'f':
				log_init(NULL, optarg);
				break;
#endif
			default:
				printf("Please read help for using!\n");
				return -1;
		}
	}

	timefunc();

	raw("on raw\n");
	err("ok err\n");
	war("ok war\n");
	inf("ok inf\n");
	dbg("ok dbg\n");
	trc("ok trc\n");

	return 0;
}
