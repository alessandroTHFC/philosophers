/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apangraz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:33:14 by apangraz          #+#    #+#             */
/*   Updated: 2022/03/20 16:33:24 by apangraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				number;
	int				xeaten;
	int				last_meal;
	struct s_info	*data;
	struct s_philo	*destra;
	pthread_mutex_t	fork;
	pthread_t		thread;
}	t_philo;

typedef struct s_info
{
	int				philo_total;
	int				die;
	int				eat;
	int				sleep;
	int				total_meals;
	int				start_time;
	bool			finished_eating;
	bool			dead;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	aux;
}	t_info;

bool	arg_chkr(int argc, char **av);

//initData.c
void	init_data(t_info *data, char **av);
void	status(t_info *data);

void	*lifecycle(void *philosopher);

//utils
int		atoi(const char *str);
int		get_time(void);
void	locked_print(t_info *data, t_philo *philo, int msg);
void	exit_free(t_info *data);
void	custom_usleep(t_info *data, int time);
int		compare(const char *s1, const char *s2, size_t n);

#endif
