/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:06 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/08/29 16:09:50 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**pars_args(int ac, char *av[])
{
	int		i;
	int		j;
	int		k;
	char 	**raw_args;
	char	*res[ac];

	if (ac > 6 || ac <= 1)
	{
		write(2, "Wrong usage\n", 12);
		exit(1);
	}
	i = 1;
	k = 0;
	res[ac] = NULL;
	while (i < ac)
	{
		if (is_white_space(av[i]))
			exit(1);
		raw_args = ft_split(av[i], ' ');
		j = 0;
		while (raw_args[j])
		{
			// chaecks : non digit, ++arg, --arg...
			res[k] = raw_args[j];
			k++;
			j++;
		}
		i++;
	}
	return (res);
}

int	main(int argc, char *argv[])
{
	int i = 0;
	char **args = pars_args(argc, argv);
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
	}
	
	return (0);
}
