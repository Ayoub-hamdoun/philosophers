/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:06 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/28 20:54:10 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_parsed_input(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->nargs > 5 || vars->nargs < 4)
	{
		write(2, "ERROR: Wrong usage\n", 19);
		return (1);
	}
	while (i < vars->nargs)
	{
		if (vars->args[i] <= 0)
		{
			write(2, "ERROR: Wrong usage\n", 19);
			return (1);
		}
		i++;
	}
	return (0);
}

int	pars_args(int ac, char *av[], t_vars *vars)
{
	char	**raw_args;

	init_vars(vars);
	while (vars->i < ac)
	{
		if (is_empty(av[vars->i]))
			return (print_error("ERROR: empty argument", NULL));
		raw_args = ft_split(av[vars->i], ' ');
		if (!raw_args)
			return (1);
		vars->j = 0;
		while (raw_args[vars->j])
		{
			if (not_valid(raw_args[vars->j]))
				return (print_error("ERROR: invalid argument", raw_args));
			vars->args[vars->k] = ft_atoi(raw_args[vars->j]);
			(vars->nargs)++;
			(vars->j)++;
			(vars->k)++;
		}
		free_2d(raw_args);
		(vars->i)++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_vars		vars;
	t_philo		*philos;

	if (pars_args(argc, argv, &vars))
		return (1);
	if (check_parsed_input(&vars))
		return (1);
	if (init_data(&data, &vars))
		return (1);
	if (init_mtx(&data))
		return (1);
	if (init_philo(&data, &philos))
		return (1);
	if (init_threads(&data, philos))
		return (1);
	return (0);
}
