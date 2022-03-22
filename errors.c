/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apangraz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:32:22 by apangraz          #+#    #+#             */
/*   Updated: 2022/03/21 10:41:36 by apangraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool	is_valid_nb(char *nb);
static bool	is_int(char *nb);

bool	arg_chkr(int argc, char **av)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 7)
	{
		printf("Invalid number of arguments\n");
		return (false);
	}
	if (*av[1] < '2')
		printf("Only 1 Philosopher? Stop wasting my time\n");
	while (av[++i])
	{
		if (!is_valid_nb(av[i]))
		{
			printf("Invalid argument included\n");
			return (false);
		}
		if (!is_int(av[i]))
		{
			printf("Argument not within the integer range\n");
			return (false);
		}
	}
	return (true);
}

static bool	is_valid_nb(char *nb)
{
	int	i;

	i = -1;
	while (nb[++i])
	{
		if (nb[i] == '-')
			return (false);
		if (!(nb[i] >= '0' && nb[i] <= '9'))
			return (false);
	}
	return (true);
}

int	length(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static bool	is_int(char *nb)
{
	int	len;

	len = length(nb);
	if (len < 10)
		return (true);
	if (len > 10 || compare(nb, "2147483648", 10) >= 0)
		return (false);
	return (true);
}
