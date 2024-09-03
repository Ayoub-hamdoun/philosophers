/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:06 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/03 16:46:05 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//tmp

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
// end tmp

void	check_nargs(int nargs)
{
	if (nargs > 5 || nargs < 4)
	{
		write(2, "Wrong usage\n", 12);
		exit(1);
	}
}

void	pars_args(int ac, char *av[], t_data *data, t_vars *v)
{
	char	**raw_args;

	v->i = 1;
	v->k = 0;
	v->j = 0;
	data->nargs = 0;
	while (v->i < ac)
	{
		if (is_empty(av[v->i]))
			print_err(0);
		raw_args = ft_split(av[v->i], ' ');
		v->j = 0;
		while (raw_args[v->j])
		{
			if (not_valid(raw_args[v->j]))
				exit(1);
			data->args[v->k] = ft_atoi(raw_args[v->j]);
			free(raw_args[v->j]);
			(data->nargs)++;
			(v->j)++;
			(v->k)++;
		}
		free(raw_args);
		(v->i)++;
	}
}

int	main(int argc, char *argv[])
{
	t_data data;
	t_vars vars;
	// struct timeval t;


	// atexit(leaks);
	pars_args(argc, argv, &data, &vars);
	check_nargs(data.nargs);
	
	// int k = 0;
	// while (k < argc)
	// {
	// 	printf("%d ", data.args[k]);
	// 	k++;
	// }
	return (0);
}
