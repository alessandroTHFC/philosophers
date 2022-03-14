#include "philosopher.h"

static bool	arg_chkr(int argc, char **av);
static bool	is_valid_nb(char *nb);
static bool	is_int(char *nb);

int	main(int argc, char **av)
{
	int	i;
	t_info	data;

	i = 0;
	if (arg_chkr(argc, av) == false)
		exit(1);
	init_data(&data, av);
	thread_genesis(&data);
	while (++i < data.philo_total)
		pthread_join(data.philo[i].thread, NULL);
	exit_free(&data);
	return (0);
}

//argChkr
//returns error message if there is only one philo, if its not a valid number, a valid integer, or not between 5-7
//arguments.

static bool	arg_chkr(int argc, char **av)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 7)
	{
		printf("Invalid number of arguments\n");
		return (false);
	}
	if (*av[1] < '2')
		printf("Only 1 Philosopher? Stop wasting my time, he's just going to die anyway\n");
	while (av[++i])
	{
		if (!is_valid_nb(av[i]))
		{
			printf("Invalid argument included, either not a number or less than 1\n");
			return (false);
		}
		if (!is_int(av[i]))
		{
			printf("Argument not within the integer range\n");
			return (false);
		}
	}
	return (true);
}

static bool	is_valid_nb(char *nb)
{
	int	i;

	i = -1;
	while (nb[++i])
	{
		if (nb[i] == '-')
			return (false);
		if (!(nb[i] >= '0' && nb[i] <= '9'))
			return (false);
	}
	return (true);
}

int	length(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static bool	is_int(char *nb)
{
	int	len;

	len = length(nb);
	if (len < 10)
		return (true);
	if (len > 10 || compare(nb, "2147483648", 10) >= 0)
		return (false);
	return (true);
}

//Status function
//called at creating of checking thread that monitors the status of each philo thread
//while there the philosophers are alive and not finished eating, it checks the current time
//against the time of the last meal and whether that is greater than the time to die. At which point
//bool value indicating death is set to true, which will cause the lifestyle function to end its while loop

void	*status(void *philosopher)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)philosopher;
	data = philo->data;
	while (!data->morto && !data->finished_eating)
	{
		if ((get_time() - philo->last_meal) > data->die)
			data->morto = true;
	}
	return (NULL);
}
