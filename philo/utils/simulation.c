/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:13:40 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/11 15:26:23 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	is_eating(t_data *data)
{
	ft_print("eating", data);
	ft_usleep(data->time_eat);
}

void	is_sleeping(t_data *data)
{
	ft_print("sleep", data);
	ft_usleep(data->time_sleep);
}

void	*start_sim(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	pthread_mutex_lock(&philo->l_fork->fork);
	printf("%ld philo %d picked left fork\n", get_current_time() - philo->data->start_sim_time, philo->id);
	pthread_mutex_lock(&philo->r_fork->fork);
	printf("%ld philo %d picked right fork\n", get_current_time() - philo->data->start_sim_time, philo->id);
	
	ft_usleep(philo->data->time_eat);
	philo->num_meals++;
	philo->time_lmeal = get_current_time() - philo->data->start_sim_time;
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);

	printf("%ld philo %d is sleeping\n", get_current_time() - philo->data->start_sim_time, philo->id);
	ft_usleep(philo->data->time_sleep);

	printf("%ld philo %d is sleeping\n", get_current_time() - philo->data->start_sim_time, philo->id);
	return (NULL);
}

//TODO - is_eating, is_sleeping, is_thinking
/*
*
*/