#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int i;

    i = 0;
    printf("\nArgc is: %i\n", argc);
    while(i < argc)
    {
        printf("\n%i is: %s\n", i, argv[i]);
        i++;
    }
    return (0);
}