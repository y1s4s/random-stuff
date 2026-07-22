#include <stdio.h>
#include <time.h>


void print_epoch(time_t *seconds)
{
    char *time_str = ctime(seconds);
    printf("%s", time_str);
}


int main()
{
    time_t time_sec = 0;
    time_t limit = 5;


    asm volatile(

        "sub sp, sp, #16\n"

        "str x19, [sp, #0]\n"
        "str x20, [sp, #8]\n"


        "mov x19, %0\n"
        "mov x20, %1\n"


        /*
            loop_start
        */
        "1:\n"


        /*
            Load time_sec
        */
        "ldr x0, [x19]\n"


        /*
            Compare:
                time_sec >= limit
        */
        "cmp x0, x20\n"


        /*
            Exit
        */
        "b.ge 2f\n"


        /*
            print_epoch(&time_sec)

        */
        "mov x0, x19\n"
        "bl _print_epoch\n"


        /*
            time_sec++

        */
        "ldr x0, [x19]\n"
        "add x0, x0, #1\n"
        "str x0, [x19]\n"


        /*
            Repeat
        */
        "b 1b\n"



        /*
            loop_end

        */
        "2:\n"

        "ldr x20, [sp, #8]\n"
        "ldr x19, [sp, #0]\n"

        "add sp, sp, #16\n"


        :
        : "r"(&time_sec), "r"(limit)
        : "x0", "x19", "x20", "memory"
    );


    return 0;
}
