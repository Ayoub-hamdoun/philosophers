/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:21:06 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/28 20:32:35 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	sizeofarray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_2d(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (i < sizeofarray(array))
		{
			if (array[i])
				free(array[i]);
			i++;
		}
		free(array);
	}
}

void	thread_joiner(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(philos[i].thread, NULL))
			printf("Error\n");
		i++;
	}
}
