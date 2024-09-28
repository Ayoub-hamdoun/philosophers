/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:06 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/28 16:01:43 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//SECTION : TMP
void *tst0()
{
	printf("msg1\n");
	sleep(3);
	printf("msg2\n");
	return NULL;
}
void leaks(void)
{
	system ("leaks philo");
}
//!SECTION

int	check_parsed_input(t_vars *vars)
{
	if (vars->nargs > 5 || vars->nargs < 4)
	{
		write(2, "ERROR: Wrong usage\n", 12);
		return (1);
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
	// t_data data; 
	t_vars 		vars;
	pthread_t 	t[vars.args[0]];
	// long i = 0;

	atexit(leaks);
	if (pars_args(argc, argv, &vars) || check_nargs(vars.nargs))
		return (1);
	printf("to the threads");
	return (0);
}
//TODO : SEE BELOW
/**
 * ft_atol instad of atoi : for >INTMAX args
 * 
 * 
 */

