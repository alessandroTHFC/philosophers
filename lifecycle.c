/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecyle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apangraz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:32:23 by apangraz          #+#    #+#             */
/*   Updated: 2022/03/22 15:13:55 by apangraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	dinner_time(t_philo *philo);
static void	get_forked(t_philo *philo);
static void	sleep_n_contemplation(t_philo *philo);

//Lifecycle
//Begins by offsetting the even numbered philosophers so that there is no deadlock. In an example where there are 4
//threads, Philosopher 1 and 3 would be free to eat, in that 1 needs his own fork and that of 2, and 3 needs his
//and that of philosopher 4. In which case, 1 and 3 would be doing there thing while 2 and 4 wait. This is achieved
//by allowing the even numbers to usleep. At which point the philosophers will enter the loop of their lifecycle.
//While there are no dead philosophers or the respective threads philosopher times eaten don't equal total meals.

void	*lifecycle(void *philosopher)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)philosopher;
	data = philo->data;
	if (philo->number % 2 == 0)
		usleep(1000);
	while (!data->dead && philo->xeaten != data->total_meals)
	{
		get_forked(philo);
		dinner_time(philo);
		sleep_n_contemplation(philo);
	}
	if (philo->xeaten == data->total_meals)
		data->finished_eating = true;
	return (NULL);
}

//locks the fork of the philo that enters this function, prints to confirm, then locks the fork of the philosopher
//to the right of the respective philosopher that has entered the function. prints to confirm this. 
static void	get_forked(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	locked_print(philo->data, philo, 1);
	pthread_mutex_lock(&philo->destra->fork);
	locked_print(philo->data, philo, 5);
}

//times eaten is incremented, followed by a print message to confirm the philosopher has begun eating. At which
//point a time value is assigned to the philosophers last_meal value. Philosopher then performs its "eating" for
//the time set upon running the program. Both forks are then unlocked, allowing the next philosopher to pick up.
static void	dinner_time(t_philo *philo)
{
	t_info	*data;

	data = philo->data;
	philo->xeaten++;
	locked_print(data, philo, 2);
	philo->last_meal = get_time();
	custom_usleep(data, data->eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->destra->fork);
}

//printing message of sleeping, sleeping for the time set to sleep, printing thinking message. 
void	sleep_n_contemplation(t_philo *philo)
{
	locked_print(philo->data, philo, 3);
	custom_usleep(philo->data, philo->data->sleep);
	locked_print(philo->data, philo, 4);
}
