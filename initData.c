#include "philosopher.h"

static void	initPhilo(t_info *data);

void	initData(t_info *data, char **av)
{
	memset(data, 0, sizeof(t_info));
	data->philoTotal = atoi(av[1]);
	data->die = atoi(av[2]);
	data->eat = atoi(av[3]);
	data->sleep = atoi(av[4]);
	if(av[5])
		data->totalMeals = atoi(av[5]);
	else
		data->totalMeals = -1;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->statusChkr, NULL);
	initPhilo(data);
}

static void	initPhilo(t_info *data)
{
	data->philo = (t_philo *)malloc(data->philoTotal * sizeof(t_philo));
	int	i = -1;
	while(++i < data->philoTotal)
	{
		data->philo[i].data = data;
		data->philo[i].xEaten = 0;
		data->philo[i].numero = i + 1;
		pthread_mutex_init(&data->philo[i].fork, NULL);
		if (i + 1 == data->philoTotal)
			data->philo[i].destra = &data->philo[0];
		else
			data->philo[i].destra = &data->philo[i + 1];
	}
}
