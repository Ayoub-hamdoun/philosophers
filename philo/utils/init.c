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
	data->finished = 0;
	data->finished_eat = 0;
	//finished _ finished eat ??
	if (data->meal_limit != -1)
		data->total_meals = data->meal_limit * data->philo_count;
	return (0);
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
	// return (init_philo(data, vars));
}

int init_mtx(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_finished_eat, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_finished, NULL))
		return (1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_count);
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return(1);
		i++;
	}
	return (0);
}

int	init_philo(t_data *data, t_vars *var, t_philo **philo)
{
	*philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!philo)
		return (1);
	var->i = 0;
	while (var->i < data->philo_count)
	{
		(*philo)->data = data;
		(*philo)->id = var->i + 1;
		(*philo)->left_fork = var->i;
		(*philo)->right_fork = (var->i + 1) % data->philo_count;
		(*philo)->last_meal = -1;
		(*philo)->meal_count = 0;
		if (pthread_mutex_init(&(*philo)[var->i].m_lastmeal, NULL))
			return (1);
		(var->i)++;
	}
	return (0);
}

// int init_threads(t_data *data, t_vars *var)
// {
// 	long	start_time;

// 	var->i = 0;
// 	data->start_time = -1;
// 	while (var->i < data->philo_count)
// 	{
// 		if (pthread_create(&data->philos[var.i].thread, NULL, &simulation, &data->philos[var->i]))
// 			return (1);
// 	}
// 	start_time = get_current_time();
// 	while (++(var->i) < data->philo_count)
// 		data->philos[var->i].last_meal = start_time;
// 	locker(&data->lock, &data->start_time, start_time);
// 	//stupid running thing ??
// 	if (pthread_create(&data->monitor, NULL, &monitoring, data))
// 		return (1);
// 	return (0);
// }

int	locker(pthread_mutex_t *mtx, void *v1, void *v2)
{
	if (pthread_mutex_lock(mtx))
		return (1);
	*v1 = *v2;
	if (pthread_mutex_unlock(mtx))
		return (1);
	return (0);
}

void	printer(t_data *data, int philo_id, char *msg)
{
	pthread_mutex_lock(&(data->print_lock));
	pthread_mutex_lock(&(data->m_finished));
	if (!data->finished)
		printf("%lld %d %s", time_diff(data->start_time), philo_id, msg);
	pthread_mutex_unlock(&(data->m_finished));
	pthread_mutex_unlock(&(data->print_lock));
}

void	*philosopher_routine(void *arg)
{
	t_data *data;
	t_philo	*philo;

	philo = arg;
	data = philo->data;
	if (philo->id % 2)
		ft_usleep(50);
	while (1)
	{
		pthread_mutex_lock(&(data.m_finished));
		if (data->finished == 1)
		{
			pthread_mutex_unlock(&(data.m_finished));
			break ;
		}
		pthread_mutex_unlock(&(data.m_finished));
		pthread_mutex_lock(&(data->forks[philo->right_fork]));
		printer(data, philo->id, "took the right fork\n");
		pthread_mutex_lock(&(data->forks[philo->left_fork]));
		printer(data, philo->id, "took the left fork\n");
		printer(data, philo->id, "eating\n");
		pthread_mutex_lock(&(philo->m_lastmeal));
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(&(philo->m_lastmeal));
		pthread_mutex_lock(&(data->finished_eat));
		data->finished_eat++;
		pthread_mutex_unlock(&(data->finished_eat));
		philo->meal_count++;
		ft_usleep(data->eat_time);
		pthread_mutex_lock(&(data->forks[philo->left_fork]));
		pthread_mutex_lock(&(data->forks[philo->right_fork]));
		printer(data, philo->id, "sleeping\n");
		ft_usleep(data->sleep_time);
		printer(data, philo->id, "thinking\n");
		ft_usleep(5);
	}
	return NULL;
}

int init_threads(t_data *data, t_philo *philos, t_vars *vars)
{
	vars->i = 0;
	while (vars->i < data->philo_count)
	{
		philos[vars->i].last_meal = get_current_time();
		if (pthread_create(&(philos[vars->i].thread), NULL, &philosopher_routine, data))
			return (1);
		(vars->i)++;
	}
	
}
