#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <pthread.h>
#include <signal.h>
#include <sched.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdbool.h>
#include <linux/unistd.h>

#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <sys/mman.h>

#include "pmc.h"

static inline uint64_t rdtsc(void)
{
	unsigned int low, high;

	asm volatile("rdtsc" : "=a" (low), "=d" (high));

	return low | ((uint64_t)high) << 32;
}

#define DEFAULT_INTERVAL 1000
#define DEFAULT_DISTANCE 500


int main(int argc, const char *argv[])
{
	if (argc !=2 ) {
		printf("input as: perf-mon count\n");
		return -1;
	}

	int count = atoi(argv[1]);
	uint64_t tsc_start;
	uint64_t tsc_stop;

	printf("loops: %d\n", count);

//	pmc_init(0);
//	pmc_init(1);

	for (int i = 0; i < count; i++) {

	
		pmc_start(0);
		pmc_start(1);

		tsc_start = rdtsc();

		sleep(3);

		tsc_stop = rdtsc();

		pmc_stop(0);
		pmc_report();

		pmc_stop(1);
		pmc_report();

		printf("TSC start:0x%lx, end:0x%lx, delta:%lu", tsc_start, tsc_stop, tsc_stop - tsc_start);

	}

	return 0;
}