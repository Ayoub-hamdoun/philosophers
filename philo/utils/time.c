/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:45:53 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/28 20:51:00 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_current_time(void)
{
	long long		current;
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	current = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current);
}

int	ft_usleep(long ms)
{
	long	i;
	long	j;

	i = get_current_time();
	if (!i)
		return (1);
	while (1)
	{
		j = get_current_time();
		if (!j)
			return (1);
		usleep(10);
		if (j - i >= ms)
			break ;
	}
	return (0);
}

long long	time_diff(long long start_sim)
{
	long long	diff;

	diff = get_current_time() - start_sim;
	if (diff < 0)
		return (0);
	return (diff);
}
