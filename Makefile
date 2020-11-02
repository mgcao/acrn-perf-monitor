
CC ?= gcc

CFLAGS += -O0 -g -Wfatal-errors -Wall

SOURCE_FILES = msr.c  pmc.c acrn_vmexit.c dram_counter.c  perf-mon.c

all:
	$(CC) -o ./perf-mon  $(SOURCE_FILES) $(CFLAGS)

clean:
	rm *.o