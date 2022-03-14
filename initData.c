#include "philosopher.h"

static void	init_philo(t_info *data);

void	init_data(t_info *data, char **av)
{
	memset(data, 0, sizeof(t_info));
	data->philo_total = atoi(av[1]);
	data->die = atoi(av[2]);
	data->eat = atoi(av[3]);
	data->sleep = atoi(av[4]);
	if (av[5])
		data->total_meals = atoi(av[5]);
	else
		data->total_meals = -1;
	pthread_mutex_init(&data->print, NULL);
	init_philo(data);
}

static void	init_philo(t_info *data)
{
	int	i;

	i = -1;
	data->philo = (t_philo *)malloc(data->philo_total * sizeof(t_philo));
	while (++i < data->philo_total)
	{
		data->philo[i].data = data;
		data->philo[i].xeaten = 0;
		data->philo[i].numero = i + 1;
		pthread_mutex_init(&data->philo[i].fork, NULL);
		if (i + 1 == data->philo_total)
			data->philo[i].destra = &data->philo[0];
		else
			data->philo[i].destra = &data->philo[i + 1];
	}
}
