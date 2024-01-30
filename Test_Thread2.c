#include "types.h"
#include "user.h"
#include "stat.h"

Lock p2_perm, p1_perm, p3_perm;

void p1(void *arg1, void *arg2)
{
    printf(0, "A\n");

    Lock_Acquire(&p2_perm);
    Lock_Release(&p1_perm);

    printf(0, "C\n");

    Lock_Acquire(&p3_perm);
    printf(0, "D\n");

    Lock_Release(&p3_perm);
    exit();
}

void p2(void *arg1, void *arg2)
{
    Lock_Acquire(&p1_perm);
    printf(0, "B\n");

    Lock_Release(&p2_perm);

    Lock_Acquire(&p3_perm);
    printf(0, "E\n");
    printf(0, "F\n");

    Lock_Release(&p3_perm);
    exit();
}

void p3(void *arg1, void *arg2)
{
    Lock_Acquire(&p3_perm);
    printf(0, "G\n");

    Lock_Release(&p2_perm);
    exit();
}

int main()
{
    Lock_Init(&p1_perm);
    Lock_Init(&p2_perm);
    Lock_Init(&p3_perm);

    Lock_Acquire(&p1_perm);

    thread_create(&p1, (void *)0, (void *)0);
    thread_create(&p2, (void *)0, (void *)0);
    thread_create(&p3, (void *)0, (void *)0);

    Lock_Release(&p2_perm);

    join(1);
    join(2);
    join(3);

    exit();
}