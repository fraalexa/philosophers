/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 07:44:29 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/13 10:26:07 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

int	check_all_ate(t_sim *sim)
{
	int	i;

	i = 0;
	if (sim->n_allowed_eat <= 0)
		return (1);
	while (i < sim->n_philo)
	{
		pthread_mutex_lock(&sim->data[i].eat_count);
		if (sim->data[i].n_eaten < sim->n_allowed_eat)
		{
			pthread_mutex_unlock(&sim->data[i].eat_count);
			return (1);
		}
		pthread_mutex_unlock(&sim->data[i].eat_count);
		i++;
	}
	pthread_mutex_lock(&sim->flag_mutex);
	sim->sim_flag = 0;
	pthread_mutex_unlock(&sim->flag_mutex);
	return (0);
}

void	*monitioring(void *arg)
{
	int		i;
	t_sim	*sim;

	sim = (t_sim *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&sim->data[i].last_meal_mutex);
		if (get_time() - sim->data[i].last_meal > sim->data[i].die_t)
		{
			print_output(sim, " died ", sim->data[i].id);
			pthread_mutex_lock(&sim->flag_mutex);
			sim->sim_flag = 0;
			pthread_mutex_unlock(&sim->flag_mutex);
			pthread_mutex_unlock(&sim->data[i].last_meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&sim->data[i].last_meal_mutex);
		if (!check_all_ate(sim))
			return (NULL);
		i = (i + 1) % sim->n_philo;
		usleep(500);
	}
}

void	*sim(void *arg)
{
	t_philo_data	*data;

	data = (t_philo_data *)arg;
	if (data->sim->n_philo == 1)
	{
		print_output(data->sim, " has taken a fork ", data->id);
		ft_usleep(data->die_t);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&data->sim->flag_mutex);
		if (!data->sim->sim_flag)
		{
			pthread_mutex_unlock(&data->sim->flag_mutex);
			break ;
		}
		pthread_mutex_unlock(&(data->sim->flag_mutex));
		eat(data);
		print_output(data->sim, " is sleeping ", data->id);
		ft_usleep(data->sleep_t);
		print_output(data->sim, " is thinking ", data->id);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int			n_philo;
	int			i;
	t_sim		sim;
	pthread_t	monitor;

	i = 0;
	if (ac < 5 || ac > 6 || !check_args(av))
	{
		printf("input error: %s n_philo die _t eat_t sleep_t n_eat\n", av[0]);
		return (1);
	}
	n_philo = f_atoi(av[1]);
	create_structs(&sim, n_philo);
	set_structs(av, &sim, n_philo);
	if (av[5])
		sim.n_allowed_eat = f_atoi(av[5]);
	else
		sim.n_allowed_eat = 0;
	set_forks(sim.data, sim.forks, n_philo);
	create_philo(n_philo, sim.philos, sim.data);
	pthread_create(&monitor, NULL, monitioring, &sim);
	while (i < n_philo)
		pthread_join(sim.philos[i++], NULL);
	pthread_join(monitor, NULL);
	free_structs(&sim);
}
