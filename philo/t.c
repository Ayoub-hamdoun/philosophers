#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
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

void init_forks(t_data *data) {
    data->forks = malloc(sizeof(t_fork) * data->n_philos);
    for (int i = 0; i < data->n_philos; i++) {
        data->forks[i].id = i;
        pthread_mutex_init(&data->forks[i].fork, NULL);
    }
}

void init_philos(t_data *data) {
    data->philos = malloc(sizeof(t_philo) * data->n_philos);
    for (int i = 0; i < data->n_philos; i++) {
        data->philos[i].id = i;
        data->philos[i].num_meals = 0;
        data->philos[i].is_dead = 0;
        data->philos[i].l_fork = &data->forks[i];
        data->philos[i].r_fork = &data->forks[(i + 1) % data->n_philos];
        data->philos[i].data = data;
    }
}

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    while (!philo->data->is_done) {
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
        philo->time_lmeal = time(NULL);

        // Put down forks
        pthread_mutex_unlock(&philo->r_fork->fork);
        pthread_mutex_unlock(&philo->l_fork->fork);

        // Sleep
        printf("Philosopher %d is sleeping\n", philo->id);
        usleep(philo->data->time_sleep);
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
    data.time_die = 10000;
    data.time_eat = 2000;
    data.time_sleep = 3000;
    data.n_meals = 3;
    data.is_done = 0;

    pthread_mutex_init(&data.print, NULL);
    init_forks(&data);
    init_philos(&data);

    create_philosopher_threads(&data);
    join_philosopher_threads(&data);
    destroy_mutexes(&data);

    free(data.forks);
    free(data.philos);

    return 0;
}