#include <stdio.h>

char *int_to_hexa(int nb)
{
    int neg;
    char base[16] = "0123456789ABCDEF";

    neg = 1;
    if (nb < 0)
        neg =-1;
    if (nb > 15)
        {
            int_to_hexa(nb/16-nb%16);
        } 
}

int main()
{
    printf("%s\n", int_to_hexa(154));
    printf("%s\n", int_to_hexa(42));
}