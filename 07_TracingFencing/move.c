#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define fperror(format, ...) fprintf(stderr, format ": %s\n", ##__VA_ARGS__, strerror(errno))

enum
{
    OK,
    WRONG_USAGE,
    WRONG_FILE,
    NO_PERM,
    OTHER_PROBLEMS
};

int error_code()
{
    switch (errno) {
    case 0:
        return OK;
    case ENAMETOOLONG:
    case ENOENT:
    case ELOOP:
        return WRONG_FILE;
    case EACCES:
    case EROFS:
    case ETXTBSY:
        return NO_PERM;
    default:
        return OTHER_PROBLEMS;
    }
}

#define check_error(...) do { \
    int exit_code = error_code(); \
    if (exit_code) { \
        fperror(__VA_ARGS__); \
        exit(exit_code); \
    } \
} while(0)


int main(int argc, char **argv)
{
    if (argc != 3) {
        puts("Usage: move INFILE OUTFILE");
        puts("Move content of INFILE file to OUTFILE file.");
        return WRONG_USAGE;
    }

    char *in_file = argv[1];
    char *out_file = argv[2];

    FILE *in_fp = fopen(in_file, "r");
    check_error("Can't open input file '%s'", in_file);

    FILE *out_fp = fopen(out_file, "w");
    check_error("Can't open output file '%s'", out_file);

    int ch;
    while ((ch = getc(in_fp)) != EOF) {
        check_error("Can't read data from input file '%s'", in_file);
        putc(ch, out_fp);
        check_error("Can't write data to output file '%s'", out_file);
    }

    fclose(in_fp);
    check_error("Can't close input file '%s'", in_file);
    fclose(out_fp);
    check_error("Can't close output file '%s'", out_file);

    remove(in_file);
    check_error("Can't remove input file '%s'", in_file);

    return OK;
}

