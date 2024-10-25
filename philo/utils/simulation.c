/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:13:40 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/10/25 22:11:21 by ayhamdou         ###   ########.fr       */
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

void	*start_sim(void *data)
{
	t_data *d = (t_data *)data;

	is_eating(d);
	is_sleeping(d);
	ft_print("think", d);
	return (NULL);
}

//TODO - is_eating, is_sleeping, is_thinking
/*
*
*/