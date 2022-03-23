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

//Main Function
//The main works by first checking the validity of the arguments supplied, must be valid number.
//(within interger range and not negative) Arguments need to be either 5 or 6 depending if total meals is supplied.
//calls init_data which initialises the main "data" struct that contains the arguments aswell as a few other values
//needed for the program to run, e.g. finished_eating, dead, aswell as a pointer to the philo struct and the mutex
//for printing. Each Philo struct contain an ID number, times eaten value, a time value of when they last ate.
//Aswell as a pointer back to the data struct, a pointer to the philosopher to his right, his mutex fork and his
//pthread_t thread. A start time is then set, right before genesis is called which uses pthread_create. At which
//point the threads will essentially branch off and begin their work executing the lifecycle function. In the mean
//time, the main process will have exited genesis and entered into the status function where it will remain, until
//something causes it to break its loop. I.E finished eating or dead. If the philo dies, it will exit directly
//from within the check_dead function. 

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

//genesis function
//while i is less than total philosophers it will create the thread stored inside each philo struct, executing
//the code stored at the function pointer, using the respective philo struct as its parameter. At which point, 
//the time of said philosophers last meal will be set to the start time, otherwise it won't work properly. 

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
