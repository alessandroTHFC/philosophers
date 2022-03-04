#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

typedef struct	s_philo
{
	int				numero;
	int				xEaten;
	int				lastMeal;
	struct s_info			*data;
	struct	s_philo			*destra;
	pthread_mutex_t fork;
	pthread_t				thread;
	pthread_t				checker;
}	t_philo;

typedef	struct	s_info
{
	int				philoTotal;
	int				die;
	int				eat;
	int				sleep;
	int				totalMeals;
	int			startTime;
	bool			finishedEating;
	bool				morto;
	t_philo				*philo;
	pthread_mutex_t		print;
}	t_info;

//initData.c
void	initData(t_info *data, char **av);

//threadGenesis.c
void	threadGenesis(t_info *data);

//utils.c
int	atoi(const char *str);
int	getTime(void);
void	lockedPrint(t_info *data, t_philo *philo, int msg);
void	exit_free(t_info *data);
int	compare(const char *s1, const char *s2, size_t n);

//main.c
void	*status(void *philosopher);
#endif
