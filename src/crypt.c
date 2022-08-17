#include "../corsair.h"

int main(int argc, char **argv)
{
    t_global2 g;
    
    if (argc != 3)
    {
        red();
        printf("\n\nThere's an error in your input, check make help for more info\n\n");
        reset();
        return (0);
    }
    if (argc == 3)
    {
        if (argv[1][0] == '1')
            encrypt_str(argv[2], &g);
        else if(argv[1][0] == '2')
        {
            if(encrypt_str(argv[2], &g) == -1)
                return (0);
            decrypt_str(&g);
        }
    }
    else
    {
        red();
        printf("\n\nThere's an error in your input, check make help for more info\n\n");
        reset();
        return (0);
    }
    return (0);
}