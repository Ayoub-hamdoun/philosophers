
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include "philo.h"

void init_forks(t_data *data) {
	data->forks = malloc(sizeof(t_fork) * data->n_philos);
	int i = 0;
	while (i < data->n_philos)
	{
		data->forks[i].id = i + 1;
		pthread_mutex_init(&data->forks[i].fork, NULL);
		i++;
	}
}

void init_philos(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	int i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].num_meals = 0;
		data->philos[i].is_dead = 0;
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[(i + 1) % data->n_philos];
		if ((i + 1) % 2 == 0)
		{
			data->philos[i].r_fork = &data->forks[(i + 1) % data->n_philos];
			data->philos[i].l_fork = &data->forks[i];
		}
		data->philos[i].data = data;
		data->philos[i].time_lmeal = get_current_time();
		i++;
	}
}

void *philosopher_routine(void *arg) {
	t_philo *philo = (t_philo *)arg;
	while (!philo->data->is_done && !philo->is_dead)
	{
		// Think

		// Pick up forks
		pthread_mutex_lock(&philo->l_fork->fork);
		printf("%ld philo %d has taken left fork \n", get_current_time() - philo->data->start_sim_time, philo->id);
		pthread_mutex_lock(&philo->r_fork->fork);
		printf("%ld philo %d has taken right fork\n", get_current_time() - philo->data->start_sim_time, philo->id);

		// Eat
		printf("%ld Philosopher %d is eating\n",get_current_time() - philo->data->start_sim_time ,philo->id);
		ft_usleep(philo->data->time_eat);
		philo->num_meals++;
		philo->time_lmeal = get_current_time();

		// Put down forks
		pthread_mutex_unlock(&philo->r_fork->fork);
		pthread_mutex_unlock(&philo->l_fork->fork);

		// Sleep
		printf("%ld Philosopher %d is sleeping\n",get_current_time() - philo->data->start_sim_time, philo->id);
		ft_usleep(philo->data->time_sleep);

		printf("Philosopher %d is thinking\n", philo->id);
	}
	return NULL;
}

void *monitor_routine(void *arg) {
	t_data *data = (t_data *)arg;
	int i = 0;
	while (!data->is_done) {
		while (i < data->n_philos) {
			long current_time = get_current_time();
			if (current_time - data->philos[i].time_lmeal > data->time_die)
			{
				data->philos[i].is_dead = 1;
				data->is_done = 1;
				printf("Philosopher %d has died\n", data->philos[i].id);
				break;
			}
			i++;
		}
		ft_usleep(10); // Sleep for a short time before checking again
	}
	return NULL;
}


void create_philosopher_threads(t_data *data) {
	int i = 0;
	while (i < data->n_philos)
	{
		pthread_create(&data->philos[i].philo_thread, NULL, philosopher_routine, &data->philos[i]);
		i++;
	}
}

void join_philosopher_threads(t_data *data) {
	int i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		i++;
	}
}

void destroy_mutexes(t_data *data) {
	int i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&data->print);
}

int main(int argc, char **argv) {
	t_data data;
	data.n_philos = 5;
	data.time_die = 100;
	data.time_eat = 200;
	data.time_sleep = 300;
	data.n_meals = 3;
	data.is_done = 0;
	data.start_sim_time = get_current_time();

	pthread_mutex_init(&data.print, NULL);
	init_forks(&data);
	init_philos(&data);

	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, monitor_routine, &data);

	create_philosopher_threads(&data);
	join_philosopher_threads(&data);

	pthread_join(monitor_thread, NULL);
	destroy_mutexes(&data);

	free(data.forks);
	free(data.philos);

	return 0;
}

// int main(int argc, char const *argv[])
// {
// 	printf("%ld vs %ld", get_current_time(), LONG_MAX);
// 	return 0;
// }
