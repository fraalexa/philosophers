/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:22:25 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/13 00:06:47 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	eat(t_philo_data *data)
{
	if (!(data->id % 2))
	{
		pthread_mutex_lock(data->left_frk);
		print_output(data->sim, " has taken a fork ", data->id);
		pthread_mutex_lock(data->right_frk);
		print_output(data->sim, " has taken a fork ", data->id);
	}
	else
	{
		pthread_mutex_lock(data->right_frk);
		print_output(data->sim, " has taken a fork ", data->id);
		pthread_mutex_lock(data->left_frk);
		print_output(data->sim, " has taken a fork ", data->id);
	}
	pthread_mutex_lock(&data->last_meal_mutex);
	data->last_meal = get_time();
	pthread_mutex_unlock(&data->last_meal_mutex);
	pthread_mutex_lock(&data->eat_count);
	data->n_eaten++;
	pthread_mutex_unlock(&data->eat_count);
	print_output(data->sim, " is eating ", data->id);
	ft_usleep(data->eat_t);
	pthread_mutex_unlock(data->right_frk);
	pthread_mutex_unlock(data->left_frk);
}

int	f_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

int	f_strcmp(char *str, char *str1)
{
	while (*str && *str1)
	{
		if (*str != *str1)
			return (1);
		str++;
		str1++;
	}
	return (*str != *str1);
}

void	print_output(t_sim *sim, char *str, int n)
{
	pthread_mutex_lock(&sim->flag_mutex);
	if (!sim->sim_flag)
	{
		pthread_mutex_unlock(&sim->flag_mutex);
		return ;
	}
	pthread_mutex_unlock(&sim->flag_mutex);
	pthread_mutex_lock(&sim->print_mutex);
	printf("%ld %d %s\n", get_time() - sim->start_time, n, str);
	pthread_mutex_unlock(&sim->print_mutex);
}
