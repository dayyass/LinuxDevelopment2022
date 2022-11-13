#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <rhash.h>
#include "config.h"

#ifdef HAVE_LIBREADLINE
#include <readline/readline.h>
#endif

int main()
{
    rhash_library_init();

    char *cmd = NULL;
    unsigned char digest[64];
    char output[130];

    while (1) {
        fflush(stderr);

#ifdef HAVE_LIBREADLINE
        cmd = readline(PACKAGE_NAME"> ");
        if (cmd == NULL) {
            break;
        }
        add_history(cmd);
#else
        printf(PACKAGE_NAME"> ");
        size_t n;
        if (getline(&cmd, &n, stdin) < 0) {
            break;
        }

        size_t cmd_len = strlen(cmd);
        if (cmd_len > 0 && cmd[cmd_len - 1] == '\n') {
            cmd[cmd_len - 1] = '\0';
        }
#endif

        char *hash_alg_name = strtok(cmd, " ");
        if (!hash_alg_name) {
            fprintf(stderr, "Error occurred while parsing hash algorithm name.\n");
            continue;
        }

        char *msg = strtok(NULL, " ");
        if (!msg) {
            fprintf(stderr, "Error occurred while parsing message to hash.\n");
            continue;
        }

        int output_type = islower(hash_alg_name[0]) ? RHPR_BASE64 : RHPR_HEX;

        for (char *p = hash_alg_name; *p; ++p) {
            *p = (char) tolower(*p);
        }
        int hash_alg = -1;
        if (strcmp(hash_alg_name, "md5") == 0) {
            hash_alg = RHASH_MD5;
        } else if (strcmp(hash_alg_name, "sha1") == 0) {
            hash_alg = RHASH_SHA1;
        } else if (strcmp(hash_alg_name, "tth") == 0) {
            hash_alg = RHASH_TTH;
        } else {
            fprintf(stderr, "Unknown name of hash algorithm.\n");
            continue;
        }

        if (msg[0] == '"') {
            // String
            int res = rhash_msg(hash_alg, msg, strlen(msg), digest);
            if (res < 0) {
                fprintf(stderr, "Message digest calculation error.\n");
                continue;
            }
        } else {
            // File
            int res = rhash_file(hash_alg, msg, digest);
            if (res < 0) {
                fprintf(stderr, "LibRHash error: %s: %s.\n", msg, strerror(errno));
                continue;
            }
        }

        rhash_print_bytes(output, digest, rhash_get_digest_size(hash_alg), output_type);

        puts(output);

#ifdef HAVE_LIBREADLINE
        free(cmd);
#endif
    }

    free(cmd);

    return 0;
}
