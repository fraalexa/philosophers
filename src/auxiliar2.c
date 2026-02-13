/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:15:06 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/13 10:31:01 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (1);
	return (0);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (ft_strcmp(av[i], "0") == 0)
			return (0);
		if (*av[i] == '-')
			return (0);
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
