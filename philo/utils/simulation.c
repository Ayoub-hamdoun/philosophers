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
	ft_usleep(data->eat_time);
}

void	is_sleeping(t_data *data)
{
	ft_print("sleep", data);
	ft_usleep(data->sleep_time);
}

void	*simulation(void *arg)
{
	t_philo *philo;
	t_data	*data;
	int		end;

	philo = (t_philo *)arg;
	data = philo->data;
	if ()
	return (NULL);
}

//TODO - is_eating, is_sleeping, is_thinking
/*
*
*/