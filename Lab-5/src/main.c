#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include "headers/GUI_lib.h"
#include "headers/SC_lib.h"
#include "headers/MT_lib.h"
#include "headers/RK_lib.h"

struct itimerval nval, oval;

void sighandler(int signum)
{
    if (signum == SIGKILL) {
        mt_clrscr();
        exit(0);
    }
    if (signum == SIGALRM) {
        int freq_flg = 0,
            comm_flg = 0,
            inst_curr = 0;
        sc_regGet(FREQ_ERR, &freq_flg);
        sc_regGet(COMMAND_ERR, &comm_flg);
        sc_instGet(&inst_curr);

        if (freq_flg || comm_flg)
            run_flg = 0;

        if (run_flg) {
            step();
            interface();
        }

        int inst_new = 0;
        sc_instGet(&inst_new);
        if (!(inst_new - inst_curr))
            run_flg = 0;
    }
}

int main()
{
    signal(SIGALRM, sighandler);
    signal(SIGKILL, sighandler);

    nval.it_interval.tv_sec = 0;
    nval.it_interval.tv_usec = 80000;
    nval.it_value.tv_sec = 0;
    nval.it_value.tv_usec = 50000;
    setitimer(ITIMER_REAL, &nval, &oval);

    init();

    simple_computer();

    write(1, "\e[0m", 4);
    rk_mytermrestore();
    mt_clrscr();
    return 0;
}
