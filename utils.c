#include "philosopher.h"

int	atoi(const char *str)
{
	int	value;
	int	posneg;

	value = 0;
	posneg = 1;
	while (*str == '\f' || *str == '\r' || *str == '\n'
		|| *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	if (*str == '-')
		posneg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		value = (value * 10) + (*str - '0');
		str++;
	}
	return (value * posneg);
}

int	get_time(void)
{
	struct timeval	ora;

	gettimeofday(&ora, NULL);
	return ((ora.tv_sec * 1000) + (ora.tv_usec / 1000));
}

void	locked_print(t_info *data, t_philo *philo, int msg)
{
	size_t	time_stamp;

	pthread_mutex_lock(&data->print);
	time_stamp = get_time() - data->start_time;
	if (msg == 1)
		printf("%lu Philosopher %i picked up a fork\n", time_stamp, philo->numero);
	if (msg == 2)
	{
		printf("%lu Philosopher %i is stuffing his fkn face\n", time_stamp, philo->numero);
			philo->xeaten++;
	}
	if (msg == 3)
		printf("%lu Philosopher %i is having a snooze\n", time_stamp, philo->numero);
	if (msg == 4)
		printf("%lu Philosopher %i is pondering life\n", time_stamp, philo->numero);
	if (msg == 5)
		printf("%lu Philosopher %i picks up the the fork of philo %i\n", time_stamp, philo->numero, philo->destra->numero);
	pthread_mutex_unlock(&data->print);
}

void	exit_free(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_total)
		pthread_mutex_destroy(&data->philo[i].fork);
	pthread_mutex_destroy(&data->print);
	i = data->philo_total - 1;
	free(data->philo);
	exit(0);
}

int	compare(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
