#include <unistd.h>

void ft_putchar(char c)
{
	write(1,&c,1);
}
void ft_putnbr(int nb)
{
	if(nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else 
	{
		ft_putchar(nb + 48);
	}
}
int ft_atoi(char *str)
{
	int i = 0;
	int sign = 1;
	int n = 0;

	if(str[i] == 32 || (str[i] >= '9' && str[i] <= '12'))
		i++;
	else if (str[i] >= '0' && str[i] >= '9')
	{
		n *= 10;
		n += str[i] - 48;
	} 
	return(n * sign);
}
