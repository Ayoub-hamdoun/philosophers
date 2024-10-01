/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:55:58 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/10/01 15:47:23 by ayhamdou         ###   ########.fr       */
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
	vars->i = 0;

	data->end_sim = 0;
	data->n_philos = vars->args[0];
	data->time_die = (long)vars->args[1];
	data->time_eat = (long)vars->args[2];
	data->time_sleep = (long)vars->args[3];
	data->n_meals = vars->args[4];
	return (0);
}
