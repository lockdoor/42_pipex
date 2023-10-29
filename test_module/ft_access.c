#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
    char    *file;

    file = "not_exited";
    if (access("not_exited", F_OK) == -1)
    {
        perror (file);
    }
    else
    {
        printf ("%s: found\n", file);
    }
    return (0);
}