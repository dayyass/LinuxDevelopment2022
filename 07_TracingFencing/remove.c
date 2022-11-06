#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*remove_ptr)(const char *path);

int remove(const char *path)
{
    if (strstr(path, "PROTECT") == NULL) {
        remove_ptr _remove = (remove_ptr) dlsym(RTLD_NEXT, "remove");
        return _remove(path);
    }
    return 0;
}
