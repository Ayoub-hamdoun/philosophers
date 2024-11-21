/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:55:58 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/21 19:33:32 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_vars(t_vars *vars)
{
	int	i;

	i = 0;
	vars->i = 1;
	vars->j = 0;
	vars->k = 0;
	vars->nargs = 0;
	while (i < 4)
		vars->args[i++] = 0;
	vars->args[4] = -1;
}

int	init_data(t_data *data, t_vars *vars)
{
	int	i;
	int philo_nbr;
	t_philo *philo;

	data->sim_end = 0;
	data->philo_count = vars->args[0];
	data->die_time = (long long)vars->args[1];
	data->eat_time = (long long)vars->args[2];
	data->sleep_time = (long long)vars->args[3];
	data->meal_limit = vars->args[4];
	data->start_time = get_current_time();
	data->total_meals = 0;
	//finished _ finished eat ??
	if (data->meal_limit != -1)
		data->total_meals = data->meal_limit * data->philo_count;

	// data->forks = malloc(sizeof(t_fork) * data->n_philos);
	// if (!(data->forks))
	// {
	// 	printf("malloc faild : t_fork");
	// 	return (1);
	// }
	// while (i < data->n_philos)
	// {
	// 	if (pthread_mutex_init(&data->forks[i].fork, NULL))
	// 	{
	// 		printf("mutex init faild");
	// 		return (1);
	// 	}
	// 	data->forks[i].id = i;
	// 	i++;
	// }
	// i = 0;
	// data->philos = malloc(sizeof(t_philo) * data->n_philos);
	// if (!(data->philos))
	// {
	// 	printf("malloc faild : t_philo");
	// 	return (1);
	// }
	// while (i < data->n_philos)
	// {
	// 	philo = &data->philos[i];
	// 	philo->data = data;
	// 	philo->id = i + 1;
	// 	philo->is_dead = 0;
	// 	philo_nbr = philo->data->n_philos;
	// 	philo->r_fork = &data->forks[i];
	// 	philo->l_fork = &data->forks[(i + 1) % data->n_philos];
	// 	if (!philo->id % 2)
	// 	{
	// 		philo->l_fork = &data->forks[i];
	// 		philo->r_fork = &data->forks[(i + 1) % data->n_philos];
	// 	}
	// 	i++;
	// }
	// i = 0;
	// while (i < data->n_philos)
	// {
	// 	pthread_create(&data->philos[i].philo_thread, NULL, &start_sim, &data->philos[i]);
	// 	i++;
	// }
	return (init_philo(data, vars));
}

int init_mtx(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->lock, NULL);
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->philo_count);
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i].frk_mtx, NULL);
		data->forks[i].id = i + 1;
		i++;
	}
	return (0);
}

int	init_philo(t_data *data, t_vars *var, t_philo *philo)
{
	var->i = 0;
	while (var->i < data->philo_count)
	{
		philo = &data->philos[var->i];
		philo->id = var->i + 1;
		philo->meal_count = 0;
		philo->last_meal = get_current_time();
		philo->dead = 0;
		philo->right_fork = &data->forks[var->i];
		philo->left_fork = &data->forks[(var->i + 1) % data->philo_count];
		if ((var->i + 1) % 2)
		{
			philo->right_fork = &data->forks[(var->i + 1) % data->philo_count];
			philo->left_fork = &data->forks[var->i];
		}
		//init mutex : philo.lstml_mx ??
		if (pthread_mutex_init(&data->forks[var->i].frk_mtx, NULL))
			return (1);
		data->forks[var->i].id = var->i;
		(var->i)++;
	}
	return (init_threads());
}

int init_threads(t_data *data, t_vars *var)
{
	long	start_time;

	var->i = 0;
	data->start_time = -1;
	while (var->i < data->philo_count)
	{
		if (pthread_create(&data->philos[var.i].thread, NULL, &simulation, &data->philos[var->i]))
			return (1);
	}
	start_time = get_current_time();
	while (++(var->i) < data->philo_count)
		data->philos[var->i].last_meal = start_time;
	locker(&data->lock, &data->start_time, start_time);
	//stupid running thing ??
	if (pthread_create(&data->monitor, NULL, &monitoring, data))
		return (1);
	return (0);
}

int	locker(pthread_mutex_t *mtx, void *v1, void *v2)
{
	if (pthread_mutex_lock(mtx))
		return (1);
	*v1 = *v2;
	if (pthread_mutex_unlock(mtx))
		return (1);
	return (0);
}
