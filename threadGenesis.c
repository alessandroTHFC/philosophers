#include "philosopher.h"

void	threadGenesis(t_info *data)
{
	int	i = -1;
	pthread_t *thread;
	thread = (pthread_t *)malloc(data->philoTotal * sizeof(pthread_t));

	while (++i < data->philoTotal)
		pthread_create(&thread[i], NULL, &lifecycle, &data->philo[i]);
}

static void	*lifecycle(void *philosopher)
{
	t_philo	*philo
	t_info	*data;

	philo = (t_philo *)philosopher;
	data = philo->data;
	if(philo->numero % 2 == 0)
		usleep(500);	
	while(!data->deaths && !data->finishedEating)
	{
		eat
	}
}
