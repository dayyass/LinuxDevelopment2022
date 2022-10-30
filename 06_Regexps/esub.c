#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "config.h"

#define PM_LIMIT 10

void regerror_exit(int error_code, regex_t *regex, char *user_msg)
{
    size_t length = regerror(error_code, regex, NULL, 0);
    char *msgbuf = (char *) malloc(length * sizeof(char));

    regerror(error_code, regex, msgbuf, length);
    fprintf(stderr, "%s: %s.\n", user_msg, msgbuf);

    free(msgbuf);
    regfree(regex);

    exit(1);
}

void check_or_print_result(char *substitution, char *string, regmatch_t *pm, int print)
{
    if (print) {
        printf("%.*s", (int) pm[0].rm_so, string);
    }

    int in_group = 0;
    for (char *p = substitution; *p; ++p) {
        if (*p == '\\') {
            if (print && in_group) {
                putchar(*p);  // Case of '\\'
            }
            in_group = 1 - in_group;
            continue;
        }

        if (!in_group) {
            if (print) {
                putchar(*p);
            }
            continue;
        }

        if (!isdigit(*p)) {
            fprintf(stderr, "Unknown escaped character in substitution in position %ld: %c.\n",
                    (p - substitution) + 1, *p);
            exit(1);
        }

        int group_num = *p - '0';
        int start_ind = (int) pm[group_num].rm_so, end_ind = (int) pm[group_num].rm_eo;
        if (start_ind < 0) {
            fprintf(stderr, "Not enough groups in regular expression for group number %d.\n", group_num);
            exit(1);
        }

        if (print) {
            printf("%.*s", end_ind - start_ind, string + start_ind);
        }

        in_group = 0;
    }

    if (in_group) {
        fprintf(stderr, "Not closed escape symbol found in the end of substitution.\n");
        exit(1);
    }

    if (print) {
        printf("%s\n", string + pm[0].rm_eo);
    }
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("Usage: %s REGEXP SUBSTITUTION STRING\n", argv[0]);
        puts("Works like \"echo 'STRING' | sed -E 's/REGEXP/SUBSTITUTION/'\" command.");
        return 1;
    }

    char *regex_string = argv[1], *substitution = argv[2], *string = argv[3];
    regex_t regex;
    int error_code;

    error_code = regcomp(&regex, regex_string, REG_EXTENDED);
    if (error_code) {
        regerror_exit(error_code, &regex, "Could not compile regex");
    }

    regmatch_t pm[PM_LIMIT];
    error_code = regexec(&regex, string, PM_LIMIT, pm, 0);
    switch(error_code) {
        case 0:  // There is match
            regfree(&regex);
            check_or_print_result(substitution, string, pm, 0);
            check_or_print_result(substitution, string, pm, 1);
            break;
        case REG_NOMATCH:  // No match
            regfree(&regex);
            printf("%s\n", string);
            break;
        default:  // Error
            regerror_exit(error_code, &regex, "Regex match failed");
    }

    return 0;
}
