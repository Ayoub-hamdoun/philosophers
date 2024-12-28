/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:12:43 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/28 20:33:12 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	printer(t_data *data, int philo_id, char *msg)
{
	pthread_mutex_lock(&(data->print_lock));
	pthread_mutex_lock(&(data->m_finished));
	if (!data->finished)
		printf("%lld %d %s", time_diff(data->start_time), philo_id, msg);
	pthread_mutex_unlock(&(data->m_finished));
	pthread_mutex_unlock(&(data->print_lock));
}

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
