#include "philosopher.h"

static void	*lifecycle(void *philosopher);
static void	get_forked(t_philo *philo, t_info *data);
static void	dinner_time(t_philo *philo, t_info *data);
static void	sleep_n_contemplation(t_philo *philo, t_info *data);

//Create the threads passing in each philosophers internal pthread_t 'thread' and one called 'checker'
//the thread will act as the philosopher, and the checker will monitor that particular thread.
//the checker thread is also detached after. Each philo thread will execute the code stored at the
//address of lifestyle function while the checker threads will be running the status function.
void	thread_genesis(t_info *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->philo_total)
	{
		pthread_create(&data->philo[i].thread, NULL, &lifecycle, &data->philo[i]);
		pthread_create(&data->philo[i].checker, NULL, &status, &data->philo[i]);
		pthread_detach(data->philo[i].checker);
	}
}

//The lifestyle function will serve as the metaphorical lifecyle of the philosopher, containing its
//routine of eating, sleeping, thinking. To provide an offset of the philosophers, there is an if
//statement seperate into odd and even by % 2. This small sleep means that if we have 4 philosophers,
//1 and 3 will go into eat first so as to avoid them from getting gridlocked. 
static void	*lifecycle(void *philosopher)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)philosopher;
	data = philo->data;
	philo->last_meal = get_time();
	if (philo->numero % 2 == 0)
		usleep(500);
	while (!data->morto && !data->finished_eating)
	{
		get_forked(philo, data);
		dinner_time(philo, data);
		sleep_n_contemplation(philo, data);
	}
	return (NULL);
}

//A small function for the philosophers to pick up their metaphorical forks, the philosopher will enter this
//function, encounter the first locking of the mutex found at the address of philo->fork, then executing the
//locked printing function to print the successful picking up (locking the fock) of the fork. It will then 
//access the mutex_t variable fork of the philosopher to his right by using the pointer that contains to that
//address and lock it. Finally, executing lock print again to confirm the lock.
static void	get_forked(t_philo *philo, t_info *data)
{
	pthread_mutex_lock(&philo->fork);
	locked_print(data, philo, 1);
	pthread_mutex_lock(&philo->destra->fork);
	locked_print(data, philo, 5);
}

//This function replicates the eating stage of the philosophers lifecyle, after exiting the previous function, 
//both mutex_t variable forks had been locked at which point, upon enter this code block, the locked print
//function is called to print the eating message. After this, the lastMeal variable is set with a time value
//returned from getTime, usleep is then called to the time duration provided time_to_eat. It is at this point
//that the two mutex variables can be unlocked. A final if statement to check if the time eaten are equal 
//to total meals, setting the bool variable finished eating to true.

static void	dinner_time(t_philo *philo, t_info *data)
{
	locked_print(data, philo, 2);
	philo->last_meal = get_time();
	usleep(data->eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->destra->fork);
	if (philo->xeaten == data->total_meals)
		data->finished_eating = true;
}
//This function acts as the sleeping and thinking part of the lifecycle.
//If the philosopher is imagined as sleeping, upon execution, the variable current is given a time value
//this is to represent a timer, when the philosopher closes his eyes and begins sleeping. A print function
//then prints the philosophers sleeping status. At this point, while nothing is dead, there is a loop designed
//to essentially keep the thread asleep for the duration of time_to_sleep. while minusing value of the time philo
//closes his eyes from the current time, each iteration of the loop, is less it will keep sleeping. until finally
//breaking once the sleep duration is greater than or equal to. This then triggers the print message of thinking.

static void	sleep_n_contemplation(t_philo *philo, t_info *data)
{
	int	current;

	current = get_time();
	locked_print(data, philo, 3);
	while (!data->morto)
	{
		if (get_time() - current >= data->sleep)
			break ;
		usleep(500);
	}
	locked_print(data, philo, 4);
}
