void commut (int no);
int election ();
void alarm_handler (int no);
void init_sched ();
int mysetjmp (int idx);
int mylongjmp (int idx);
void new_proc (void (*f)(int), int arg);
void start_sched ();
void dummy_function (int arg);
