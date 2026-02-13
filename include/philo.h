/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 08:59:00 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/12 06:08:16 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_sim	t_sim;

typedef struct philo_data
{
	int				id;
	int				sleep_t;
	int				eat_t;
	int				die_t;
	int				n_eaten;
	long			last_meal;
	t_sim			*sim;
	pthread_mutex_t	eat_count;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*left_frk;
	pthread_mutex_t	*right_frk;	
}	t_philo_data;

typedef struct s_sim
{
	int				n_philo;
	int				n_allowed_eat;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	t_philo_data	*data;
	int				sim_flag;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	print_mutex;
	long			start_time;
}	t_sim;

void	*sim(void *arg);
void	print_output(t_sim *sim, char *str, int n);
void	set_structs(char **av, t_sim *sim, int n_philo);
void	set_forks(t_philo_data *data, pthread_mutex_t *forks, int n_philos);
void	create_structs(t_sim *sim, int n_philos);
int		create_philo(int n_philo, pthread_t *philos, t_philo_data *data);
long	get_time(void);
void	ft_usleep(long ms);
void	eat(t_philo_data *data);
int		f_atoi(char *str);
void	free_structs(t_sim *sim);
#endif