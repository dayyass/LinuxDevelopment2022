#include <stdio.h>
#include <string.h>

int main()
{
    char world[256];
    fgets(world, sizeof(world), stdin);
    world[strlen(world) - 1] = '\0';
    printf("Hello, %s!\n", world);
    return 0;
}
