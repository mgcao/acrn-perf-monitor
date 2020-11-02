#if !defined(__PMC_H__)
#define __PMC_H__

bool pmc_init(int cpu);

void pmc_start(int cpu);
void pmc_stop(int cpu);

void pmc_report(void);
#endif