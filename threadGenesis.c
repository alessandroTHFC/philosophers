#include "philosopher.h"

static void	*lifecycle(void *philosopher);
static void	getForked(t_philo *philo, t_info *data);
static void	dinnerTime(t_philo *philo, t_info *data);
static void	sleepNcontemplation(t_philo *philo, t_info *data);

void	threadGenesis(t_info *data)
{
	int	i = -1;
	pthread_t *thread;
	thread = (pthread_t *)malloc(data->philoTotal * sizeof(pthread_t));
	data->startTime = getTime();
	while (++i < data->philoTotal)
		pthread_create(&thread[i], NULL, &lifecycle, &data->philo[i]);
}

static void	*lifecycle(void *philosopher)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)philosopher;
	data = philo->data;
	if(philo->numero % 2 == 0)
		usleep(500);	
	while(!data->morto && !data->finishedEating)
	{
		getForked(philo, data);
		dinnerTime(philo, data);
		sleepNcontemplation(philo, data);
	}
	return(0);
}

static void getForked(t_philo *philo, t_info *data)
{
	pthread_mutex_lock(&philo->fork);
	lockedPrint(data, philo, 1);
	pthread_mutex_lock(&philo->destra->fork);
	lockedPrint(data, philo, 1);
}

static void dinnerTime(t_philo *philo, t_info *data)
{
	lockedPrint(data, philo, 2);
	philo->lastMeal = getTime();
	usleep(data->eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->destra->fork);
	if (philo->xEaten == data->totalMeals)
		data->finishedEating = true;
}

static void sleepNcontemplation(t_philo *philo, t_info *data)
{
	int	current;

	current = getTime();
	lockedPrint(data, philo, 3);
	while(!data->morto)
	{
		if(getTime() - current >= data->sleep)
			break ;
		usleep(100);
	}
	lockedPrint(data, philo, 4);
}
