#include "types.h"
#include "user.h"
#include "stat.h"

#define NUM_THREADS 3

struct thread_args
{
    int tid;
};

Lock my_lock;

void thread_function(void *arg1, void *arg2)
{
    struct thread_args *args = (struct thread_args *)arg2;

    Lock_Acquire(&my_lock);
    printf(2, "Thread %d finished with value = %d\n", args->tid, 2 * args->tid + 1);
    Lock_Release(&my_lock);

    free(args);
    exit();
}

int main()
{
    printf(0, "*** This program will calculate 2x+1 for %d threads where x is the tid passed to the thread as its 2nd arg ***\n", NUM_THREADS);

    Lock_Init(&my_lock);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        struct thread_args *args = (struct thread_args *)malloc(sizeof(struct thread_args));
        args->tid = i + 1;

        thread_create(&thread_function, 0, args);
    }

    for (int i = 1; i <= NUM_THREADS; i++)
    {
        join(i);
    }

    exit();
}