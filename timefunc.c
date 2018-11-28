#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

struct timeval tvs;

/*func: is a timer for delay and so on
 *auth: haibing.an
 *data: 2018-11-28
 *dscp: set s/ms/us for delay by select block
 **/

void timer4handle(int type, long seconds) {
	struct timeval wait_time;
	gettimeofday(&tvs, 0);
	switch(type) {
		case 1:                 //unit is second
			wait_time.tv_sec = seconds;
			wait_time.tv_usec = 0;
			break;
		case 2:                 //unit is millisecond
			wait_time.tv_sec = 0;
			wait_time.tv_usec = seconds * 1000;
			break;
		case 3:                 //unit is microsecond
			wait_time.tv_sec = 0;
			wait_time.tv_usec = seconds;
			break;
		default :
			break;
	}

	select(0, NULL, NULL, NULL, &wait_time);
}

void timefunc(){
	int count_num = 0;
	for (count_num = 0;count_num <= 3;count_num++) {
		printf ("Showing timer for delay %d\n", count_num);
		timer4handle(1,1);
	}
}
