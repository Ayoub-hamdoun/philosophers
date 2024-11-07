#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_fork {
    int id;
    pthread_mutex_t fork;
} t_fork;

typedef struct s_data {
    int n_philos;
    long time_die;
    long time_eat;
    long time_sleep;
    int n_meals;
    long start_sim_time;
    int is_done;
    pthread_mutex_t print;
    t_fork *forks;
    struct s_philo *philos;
} t_data;

typedef struct s_philo {
    int id;
    int num_meals;
    long time_lmeal;
    int is_dead;
    pthread_t philo_thread;
    t_fork *l_fork;
    t_fork *r_fork;
    t_data *data;
} t_philo;

long	get_current_time(void)
{
	long			current;
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	current = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current);
}

void init_forks(t_data *data) {
    data->forks = malloc(sizeof(t_fork) * data->n_philos);
    for (int i = 0; i < data->n_philos; i++) {
        data->forks[i].id = i;
        pthread_mutex_init(&data->forks[i].fork, NULL);
    }
}

void init_philos(t_data *data) {
    data->philos = malloc(sizeof(t_philo) * data->n_philos);
    long ct = get_current_time();
    for (int i = 0; i < data->n_philos; i++) {
        data->philos[i].id = i;
        data->philos[i].num_meals = 0;
        data->philos[i].is_dead = 0;
        data->philos[i].l_fork = &data->forks[i];
        data->philos[i].r_fork = &data->forks[(i + 1) % data->n_philos];
        data->philos[i].data = data;
        data->philos[i].time_lmeal = ct;
    }
}

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    while (!philo->data->is_done && !philo->is_dead) {
        // Think
        printf("Philosopher %d is thinking\n", philo->id);
        usleep(philo->data->time_sleep);

        // Pick up forks
        pthread_mutex_lock(&philo->l_fork->fork);
        pthread_mutex_lock(&philo->r_fork->fork);

        // Eat
        printf("Philosopher %d is eating\n", philo->id);
        usleep(philo->data->time_eat);
        philo->num_meals++;
        philo->time_lmeal = get_current_time();

        // Put down forks
        pthread_mutex_unlock(&philo->r_fork->fork);
        pthread_mutex_unlock(&philo->l_fork->fork);

        // Sleep
        printf("Philosopher %d is sleeping\n", philo->id);
        usleep(philo->data->time_sleep);
    }
    return NULL;
}

void *monitor_routine(void *arg) {
    t_data *data = (t_data *)arg;
    while (!data->is_done) {
        for (int i = 0; i < data->n_philos; i++) {
            long current_time = get_current_time();
            if (current_time - data->philos[i].time_lmeal > data->time_die || (data->philos[i].num_meals == data->n_meals)) {
                data->philos[i].is_dead = 1;
                data->is_done = 1;
                printf("Philosopher %d has died\n", data->philos[i].id);
                break;
            }
        }
        usleep(50); // Sleep for a short time before checking again
    }
    return NULL;
}


void create_philosopher_threads(t_data *data) {
    for (int i = 0; i < data->n_philos; i++) {
        pthread_create(&data->philos[i].philo_thread, NULL, philosopher_routine, &data->philos[i]);
    }
}

void join_philosopher_threads(t_data *data) {
    for (int i = 0; i < data->n_philos; i++) {
        pthread_join(data->philos[i].philo_thread, NULL);
    }
}

void destroy_mutexes(t_data *data) {
    for (int i = 0; i < data->n_philos; i++) {
        pthread_mutex_destroy(&data->forks[i].fork);
    }
    pthread_mutex_destroy(&data->print);
}

int main(int argc, char **argv) {
    t_data data;
    data.n_philos = 5;
    data.time_die = 100000;
    data.time_eat = 2000;
    data.time_sleep = 3000;
    data.n_meals = 3;
    data.is_done = 0;

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