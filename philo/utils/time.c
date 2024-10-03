/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:45:53 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/10/03 15:44:27 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_current_time()
{
	long			current;
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	current = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current);
}

long	ft_usleep(long ms)
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
		usleep(50);
		if (j - i >= ms)
			break;
	}
	return (0);
}


// int main(int argc, char const *argv[])
// {
// 	long t1 = get_current_time();
// 	usleep(800000);
// 	// ft_usleep(800);
// 	long t2 = get_current_time();

// 	printf("%ld",t2 - t1);
// 	return 0;
// }
