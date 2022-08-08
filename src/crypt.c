#include "../corsair.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        red();
        printf("\n\nI need exactly 3 arguments, check make help for more info\n\n");
        reset();
        return (0);
    }
    decrypt('j');//UTILIZA UN ITOA PARA PASARSELO AL BN_DEC2BN
    return (0);
}