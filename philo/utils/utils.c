/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:32:24 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/08/29 11:42:06 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//ft_atoi
int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	is_white_space(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

int	contains_non_dig(char *str)
{
	int	i;
	int	e;

	if (!str)
		return (1);
	i = 0;
	e = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			e++;
			break ;
		}
		i++;
	}
	if (e)
		return (1);
	return (0);
}
