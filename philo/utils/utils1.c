/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:12:43 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/10/25 21:57:46 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print(char *str, t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("%s\n", str);
	pthread_mutex_unlock(&data->print);
}

//TODO : print data based on type : d for timestamps, s for simple msgs...;