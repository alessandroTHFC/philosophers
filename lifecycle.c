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

static void	get_forked(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	locked_print(philo->data, philo, 1);
	pthread_mutex_lock(&philo->destra->fork);
	locked_print(philo->data, philo, 5);
}

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

void	sleep_n_contemplation(t_philo *philo)
{
	locked_print(philo->data, philo, 3);
	custom_usleep(philo->data, philo->data->sleep);
	locked_print(philo->data, philo, 4);
}
