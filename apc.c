#include "apc.h"

int validate_operand(char *str)
{
    int i = 0;

    if (str[i] == '\0')
    {
        return -1;
    }

    if (str[i] == '+' || str[i] == '-')
    {
        i++;
    }

    if (str[i] == '\0')
    {
        return -1;
    }

    if (str[i] == '0' && str[i + 1] != '\0')
    {
        return -1;
    }

    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return -1;
        }
        i++;
    }

    return 0;
}


