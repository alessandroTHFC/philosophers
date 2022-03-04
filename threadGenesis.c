#include "philosopher.h"

static void	*lifecycle(void *philosopher);
static void	getForked(t_philo *philo, t_info *data);
static void	dinnerTime(t_philo *philo, t_info *data);
static void	sleepNcontemplation(t_philo *philo, t_info *data);

void	threadGenesis(t_info *data)
{
	int	i = -1;
	data->startTime = getTime();
	while (++i < data->philoTotal)
	{	
		pthread_create(&data->philo[i].thread, NULL, &lifecycle, &data->philo[i]);
		pthread_create(&data->philo[i].checker, NULL, &status, &data->philo[i]);
		pthread_detach(data->philo[i].checker);
	}

}

static void	*lifecycle(void *philosopher)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)philosopher;
	data = philo->data;
	philo->lastMeal = getTime();
	if(philo->numero % 2 == 0)
		usleep(5);
	//printf("p%i last meal set as %i\n", philo->numero, philo->lastMeal);	
	while(!data->morto && !data->finishedEating)
	{
		getForked(philo, data);
		dinnerTime(philo, data);
		sleepNcontemplation(philo, data);
		//printf("(p%i) morto %i and finished %i xEaten is %i\n", philo->numero, data->morto, data->finishedEating, philo->xEaten);
	}
	return(NULL);
}

static void getForked(t_philo *philo, t_info *data)
{
	//printf("@@@@@philo %i enters xEaten is %i\n", philo->numero, philo->xEaten);
	pthread_mutex_lock(&philo->fork);
	lockedPrint(data, philo, 1);
	pthread_mutex_lock(&philo->destra->fork);
	lockedPrint(data, philo, 5);
}

static void dinnerTime(t_philo *philo, t_info *data)
{
	lockedPrint(data, philo, 2);
	philo->lastMeal = getTime();
	//printf("philo %i lastMeal @ %i\n", philo->numero, philo->lastMeal);
	usleep(data->eat * 1000);
	//printf("this is xEaten increasing %i\n", philo->xEaten++);
	pthread_mutex_unlock(&philo->fork);
	//printf(">>>>>p%i has put down his fork\n", philo->numero);
	pthread_mutex_unlock(&philo->destra->fork);
	//printf(">>>p%i has put down p%is fork\n", philo->numero, philo->destra->numero);
	//printf("totalMeals = %i and p%i has eaten %i times\n", data->totalMeals, philo->numero, philo->xEaten);
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
		usleep(500);
	}
	lockedPrint(data, philo, 4);
}
