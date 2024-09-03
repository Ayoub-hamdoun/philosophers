/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:32:24 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/03 15:42:48 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	signe;
	int		res;
	long	temp;

	i = 0;
	signe = 1;
	res = 0;
	temp = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if (temp > res)
			return (-1);
		temp = res;
	}
	return (res * signe);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	is_empty(char *str)
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

int	not_valid(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || (str[i] == '+')))
			return (1);
		if (str[i] == '+')
		{
			if (str[i + 1] == '+' || str[i + 1] == '-')
				return (1);
		}
		i++;
	}
	return (0);
}
