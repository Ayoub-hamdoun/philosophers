/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:21:06 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/28 15:21:32 by ayhamdou         ###   ########.fr       */
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


