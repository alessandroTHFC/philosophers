/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apangraz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:32:23 by apangraz          #+#    #+#             */
/*   Updated: 2022/03/22 12:27:18 by apangraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	check_death(t_info *data);
static void	genesis(t_info *data);

int	main(int argc, char **av)
{
	int		i;
	t_info	data;

	i = -1;
	if (arg_chkr(argc, av) == false)
		exit(1);
	init_data(&data, av);
	data.start_time = get_time();
	genesis(&data);
	status(&data);
	while (++i < data.philo_total)
		pthread_join(data.philo[i].thread, NULL);
	exit_free(&data);
	return (0);
}

static void	genesis(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_total)
	{
		pthread_create(&data->philo[i].thread, NULL,
			&lifecycle, &data->philo[i]);
		data->philo[i].last_meal = data->start_time;
	}
}

void	status(t_info *data)
{
	while (!data->finished_eating && !data->dead)
		check_death(data);
}

static void	check_death(t_info *data)
{
	int	i;

	i = -1;
	while (!data->dead && ++i < data->philo_total)
	{
		if (get_time() - data->philo[i].last_meal >= data->die)
		{
			data->dead = true;
			locked_print(data, data->philo, 6);
			exit_free(data);
		}
	}
}
