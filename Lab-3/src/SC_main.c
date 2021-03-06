#include "BC_lib.h"
#include "MT_lib.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int *alph = NULL;

void print_mem()
{
    bc_box(1, 1, 61, 12);
    mt_gotoXY(30, 0);
    char tmp[] = " Memory ";
    write(1, tmp, sizeof(tmp));
    for (int i = 0; i < 100; i++) {
        mt_gotoXY(2 + 6 * (i / 10), 2 + (i % 10));
        char tmp1[] = "+0000";
        write(1, tmp1, sizeof(tmp1));
    }
}

void print_accum()
{
    bc_box(62, 1, 22, 3);
    mt_gotoXY(66, 1);
    char tmp[] = " accumulator ";
    write(1, tmp, sizeof(tmp));
    mt_gotoXY(71, 2);
    char tmp1[] = "+9999";
    write(1, tmp1, sizeof(tmp1));
}

void print_instcnt()
{
    bc_box(62, 4, 22, 3);
    mt_gotoXY(63, 4);
    char tmp[] = " instructionCounter ";
    write(1, tmp, sizeof(tmp));
    mt_gotoXY(71, 5);
    char tmp1[] = "+0000";
    write(1, tmp1, sizeof(tmp1));
}

void print_operation()
{
    bc_box(62, 7, 22, 3);
    mt_gotoXY(68, 7);
    char tmp[] = " Operation ";
    write(1, tmp, sizeof(tmp));
    char tmp1[] = "+00 : 00";
    mt_gotoXY(69, 8);
    write(1, tmp1, sizeof(tmp1));
}

void print_flg()
{
    bc_box(62, 10, 22, 3);
    mt_gotoXY(69, 10);
    char tmp[] = " Flags ";
    write(1, tmp, strlen(tmp));
    char tmp1[] = "O Z M F C";
    mt_gotoXY(67, 11);
    write(1, tmp1, strlen(tmp1));
}

void print_membc()
{
    bc_box(1, 13, 50, 10);
    int big[] = {alph[16 * 2], alph[16 * 2 + 1]};
    bc_printbigchar(big, 2, 14, white, black);
    int big1[] = {alph[9 * 2], alph[9 * 2 + 1]};
    for (int i = 0; i < 4; i++)
        bc_printbigchar(big1, 2 + 10 * (i + 1), 14, white, black);
}

void print_keys()
{
    bc_box(51, 13, 33, 10);
    mt_gotoXY(52, 13);
    char tmp[] = " Keys: ";
    write(1, tmp, strlen(tmp));
    char *tmp1[] = {"L - Load", "S - Save", "R - Run", "T - sTep", "I - Reset",
        "F5 - accumulator", "F6 - instructionCounter"};
    for (int i = 0; i < 7; i++) {
        mt_gotoXY(52, 14 + i);
        write(1, tmp1[i], strlen(tmp1[i]));
    }
}

int main()
{
    int fd = open("font", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int cnt = 0;
    alph = (int*) malloc(sizeof(int) * 2 * 17);
    if (bc_bigcharread(fd, alph, 17, &cnt) == -1)
        return -1;
    mt_clrscr();
    print_mem();
    print_accum();
    print_instcnt();
    print_operation();
    print_flg();
    print_membc();
    print_keys();
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}