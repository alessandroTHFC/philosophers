/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apangraz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:32:23 by apangraz          #+#    #+#             */
/*   Updated: 2022/03/22 15:13:18 by apangraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_time(void)
{
	struct timeval	ora;

	gettimeofday(&ora, NULL);
	return ((ora.tv_sec * 1000) + (ora.tv_usec / 1000));
}

//locked print
//The printing function used for the program, upon entering this function, it gets locked using the print mutex
//this prevents multiple threads trying to enter this function and printing messages at the same time which could 
//cause unpredictable behaviours. I included the if(!dead) condition as, i was encountering a problem that
//even after a philosopher had died, messages were still being printed at the exact time of death or very close to
//that time. 
void	locked_print(t_info *data, t_philo *philo, int msg)
{
	size_t	time_stamp;

	pthread_mutex_lock(&data->print);
	time_stamp = get_time() - data->start_time;
	if (!data->dead)
	{	
		if (msg == 1)
			printf("%lu Philosopher %i picked up a fork\n",
				time_stamp, philo->number);
		if (msg == 2)
			printf("%lu Philosopher %i is stuffing his fkn face\n",
				time_stamp, philo->number);
		if (msg == 3)
			printf("%lu Philosopher %i is having a snooze\n",
				time_stamp, philo->number);
		if (msg == 4)
			printf("%lu Philosopher %i is pondering life\n",
				time_stamp, philo->number);
		if (msg == 5)
			printf("%lu Philosopher %i picks up the the fork of philo %i\n",
				time_stamp, philo->number, philo->destra->number);
	}
	if (msg == 6 && !data->finished_eating)
		printf("%lu Philosopher %i is dead\n", time_stamp, philo->number);
	pthread_mutex_unlock(&data->print);
}

void	custom_usleep(t_info *data, int time)
{
	int	current;

	current = get_time();
	while (!(data->dead))
	{
		if (get_time() - current >= time)
			break ;
		usleep(100);
	}
}

void	exit_free(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_total)
		pthread_mutex_destroy(&data->philo[i].fork);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->aux);
	free(data->philo);
	exit(0);
}
