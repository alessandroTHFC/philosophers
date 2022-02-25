#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct	s_philo
{
	int				numero;
	int				xEaten;
	size_t			lastMeal;
	s_info			*data;
	s_philo			*destra;
	pthread_mutex_t fork;
}	t_philo;

typedef	struct	s_info
{
	int				philoTotal;
	int				die;
	int				eat;
	int				sleep;
	int				totalMeals;
	size_t			startTime;
	bool			finishedEating;
	int				morto;
	pthread_mutex_t	print;
	pthread_mutex_t	statusChkr;
}	t_info;

//initData.c
void	initData(t_info *data, char **av);

//threadGenesis.c
void	threadGenesis(t_info *data);

//utils.c
int	atoi(const char *str);
size_t	time(void);
void	lockedPrint(t_info *data, t_philo *philo, char *msg);
