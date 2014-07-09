#ifndef __CALLOUT
#define __CALLOUT

#define CALLOUT_SIZE 10

void timeout(void (*fun)(), void* args, int tim);

void restart(void);

struct callo{
	int ctime;
	void* arg;
	void (*c_func)();
};

struct callo ve_callout[CALLOUT_SIZE];


#endif