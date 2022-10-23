#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int start, stop, step;
    int i;
} range;

void argparse(int argc, char *argv[], int *start, int *stop, int *step)
{
    if (argc == 1 || argc > 4) {
        puts("Usage: range STOP");
        puts("   or: range START STOP");
        puts("   or: range START STOP STEP");
        puts("Print numbers from START to STOP, in steps of STEP.");
        puts("If STEP is omitted, it defaults to 1.");
        puts("If START is omitted, it defaults to 0.");
        exit(0);
    }

    *start = 0, *step = 1;
    if (argc == 2) {
        *stop = (int) strtol(argv[1], NULL, 10);
    } else {
        *start = (int) strtol(argv[1], NULL, 10);
        *stop = (int) strtol(argv[2], NULL, 10);
        if (argc == 4) {
            *step = (int) strtol(argv[3], NULL, 10);
        }
    }
}

void range_init(range *r)
{
    r->i = r->start;
}

bool range_run(range *r)
{
    return r->i < r->stop;
}

void range_next(range *r)
{
    r->i += r->step;
}

int range_get(range *r)
{
    return r->i;
}

int main(int argc, char *argv[]) {
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);
    for(range_init(&I); range_run(&I); range_next(&I))
        printf("%d\n", range_get(&I));
    return 0;
}

