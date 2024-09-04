/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:39:06 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/04 17:50:12 by ayhamdou         ###   ########.fr       */
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

	initvars(v);
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
			if (data->args[v->k] < 0)
				exit(1); //TODO - cleanup function here
			(v->k)++;
		}
		free(raw_args);
		(v->i)++;
	}
}

void	*todo(void *i)
{
	
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_data data;
	t_vars vars;
	pthread_t t[data.args[0]];
	long i = 0;

	// atexit(leaks);
	pars_args(argc, argv, &data, &vars);
	check_nargs(data.nargs);
	while (i < data.args[0])
	{
		pthread_create(&t[i], NULL, todo, (void *)i);
		i++;
	}
	i = 0;
	while (i < data.args[0])
	{
		pthread_join(t[i], NULL);
		i++;
	}
	printf("finished");
	pthread_exit(NULL);
	return (0);
}
//TODO : function to craete threads 
