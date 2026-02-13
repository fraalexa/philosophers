/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:35:50 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/12 05:36:57 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_structs(t_sim *sim, int n_philos)
{
	int	i;

	i = 0;
	sim->philos = malloc(sizeof(pthread_t) * n_philos);
	sim->data = malloc(sizeof(t_philo_data) * n_philos);
	sim->forks = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (!sim->philos || !sim->data || !sim->forks)
	{
		free_structs(sim);
		return ;
	}
	while (i < n_philos)
	{
		pthread_mutex_init(&(sim->forks[i++]), NULL);
	}
	pthread_mutex_init(&(sim->print_mutex), NULL);
	pthread_mutex_init(&(sim->flag_mutex), NULL);
}

void	set_structs(char **av, t_sim *sim, int n_philo)
{
	int	i;

	i = 0;
	sim->sim_flag = 1;
	sim->n_philo = n_philo;
	sim->start_time = get_time();
	while (i < n_philo)
	{
		sim->data[i].id = i + 1;
		sim->data[i].sleep_t = f_atoi(av[4]);
		sim->data[i].eat_t = f_atoi(av[3]);
		sim->data[i].die_t = f_atoi(av[2]);
		sim->data[i].n_eaten = 0;
		sim->data[i].last_meal = sim->start_time;
		sim->data[i].sim = sim;
		pthread_mutex_init(&sim->data[i].eat_count, NULL);
		pthread_mutex_init(&sim->data[i].last_meal_mutex, NULL);
		i++;
	}
}

void	set_forks(t_philo_data *data, pthread_mutex_t *forks, int n_philos)
{
	int	i;

	data[0].left_frk = &forks[n_philos - 1];
	data[0].right_frk = &forks[0];
	i = 1;
	while (i < n_philos)
	{
		data[i].left_frk = &forks[i - 1];
		data[i].right_frk = &forks[i];
		i++;
	}
}

int	create_philo(int n_philo, pthread_t *philos, t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_create(&philos[i], NULL, sim, &data[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_structs(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->n_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	i = 0;
	while (i < sim->n_philo)
	{
		pthread_mutex_destroy(&sim->data[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->flag_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	free(sim->philos);
	free(sim->forks);
	free(sim->data);
}
