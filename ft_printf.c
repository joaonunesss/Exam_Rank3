#include<stdio.h>
#include<stdarg.h>
#include<unistd.h>
#include<stdlib.h>

void put_string(char *str, int *len)
{
    int i = -1;

    if(!str)
        str = "(null)";
    while(str[++i])
        *len += write(1, &str[i], 1);

}

void put_digit(long nbr, int base, int *len)
{
    char *hexa = "0123456789abcdef";

    if(nbr < 0)
    {
        nbr = -nbr;
        *len += write(1, "-", 1);
    }
    if(nbr >= base)
        put_digit(nbr / base, base, len);
    *len += write(1, &hexa[nbr % base], 1);
}

int ft_printf(const char *str, ...)
{
    va_list(args);
    va_start(args, str);

    int i = -1, len = 0;

    while(str[++i])
    {
        if(str[i] == '%')
        {
            i++;
            if(str[i] == 's')
                put_string(va_arg(args, char *), &len);
            else if(str[i] == 'd')
                put_digit(va_arg(args, int), 10, &len);
            else if(str[i] == 'x')
                put_digit(va_arg(args, unsigned int), 16, &len);
        }
        else
            len += write(1, &str[i], 1);
    }
    va_end(args);
    return(len);
}

// int main()
// {
//     ft_printf("%s\n", "toto");
//     ft_printf("Magic %s is %d\n", "number", 42);
//     ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// }