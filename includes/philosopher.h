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
	int				numero;
	int				xeaten;
	int				last_meal;
	struct s_info			*data;
	struct s_philo			*destra;
	pthread_mutex_t			fork;
	pthread_t			thread;
	pthread_t			checker;
}	t_philo;

typedef struct s_info
{
	int				philo_total;
	int				die;
	int				eat;
	int				sleep;
	int				total_meals;
	int				start_time;
	bool				finished_eating;
	bool				morto;
	t_philo				*philo;
	pthread_mutex_t			print;
}	t_info;

//initData.c
void	init_data(t_info *data, char **av);

//threadGenesis.c
void	thread_genesis(t_info *data);

//utils.c
int	atoi(const char *str);
int	get_time(void);
void	locked_print(t_info *data, t_philo *philo, int msg);
void	exit_free(t_info *data);
int	compare(const char *s1, const char *s2, size_t n);

//main.c
void	*status(void *philosopher);
#endif
