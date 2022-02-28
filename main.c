#include "philosopher.h"

static bool	argChkr(int argc, char **av);
static bool	isValidNb(char *nb);
static bool	isInt(char *nb);

int	main(int argc, char **av)
{
	t_info	data;

	if (argChkr(argc, av))
	{
		initData(&data, av);
		threadGenesis(&data);
	}
	return(0);
}

static bool	argChkr(int argc, char **av)
{
	int	i = 0;
	if (argc < 5 || argc > 7)
	{
		printf("Invalid number of arguments");
		return(false);
	}
	if(*av[1] < 2)
	{
		printf("Only 1 Philosopher? Stop wasting my time, he's just going to die anyway");
	}
	while (av[++i])
	{
		if (!isValidNb(av[i]))
		{
			printf("Invalid argument included, either not a number or less than 1");
			return (false);
		}
		if (!isInt(av[i]))
		{
			printf("Argument not within the integer range");
			return (false);
		}
	}
	return(true);
}

static bool	isValidNb(char *nb)
{
	int	i = -1;
	while (nb[++i])
	{
		if (nb[i] == '-')
			return (false);
		if (!(nb[i] >= '0' && nb[i] <= '9'))
			return (false);
	}
	return (true);
}

static bool	isInt(char *nb)
{
	long int	num = atoi(nb);
	if (num < -2147483648 || num > 2147483648)
		return (false);
	return (true);
}
