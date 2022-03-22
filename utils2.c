/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apangraz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:32:23 by apangraz          #+#    #+#             */
/*   Updated: 2022/03/20 16:32:23 by apangraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
