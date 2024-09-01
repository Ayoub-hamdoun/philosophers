/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:06 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/01 18:05:03 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//tmp
void leaks(void)
{
	system ("leaks philo");
}
// end tmp

void	pars_args(int ac, char *av[], t_data *data)
{
	int		i;
	int		j;
	int		k;
	char 	**raw_args;

	if (ac > 6 || ac <= 1)
	{
		write(2, "Wrong usage\n", 12);
		exit(1);
	}
	i = 1;
	k = 0;
	while (i < ac)
	{
		if (is_white_space(av[i]))
		{
			printf("hehe");
			exit(1);
		}
		raw_args = ft_split(av[i], ' ');
		j = 0;
		while (raw_args[j])
		{
			if (not_valid(raw_args[j]))
				exit(1);
			data->structarg[k] = ft_atoi(raw_args[j]);
			free(raw_args[j]);
			j++;
			k++;
		}
		free(raw_args);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data data;

	pars_args(argc, argv, &data);
	atexit(leaks);
	printf("%d, %d, %d, %d, %d", data.structarg[0], data.structarg[1], data.structarg[2], data.structarg[3], data.structarg[4]);
	return (0);
}
"12 12  2" 22  2222