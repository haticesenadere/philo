#include "philo.h"

static void	destroy_forks(t_shared *shared, int limit)
{
	int	i;

	/* Loop: 0 to limit-1 mutex'i temizle */
	i = 0;
	while (i < limit)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		i++;
	}
}

static int init_forks(t_shared *shared)
{
    int i;

    i = 0;
    while (i < shared->count)
    {
        if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
        {   
            destroy_forks(shared, i);
            return (1);
        }
        i++;
    }
    return (0);
}

int init_shared(t_shared *shared)
{
    shared->finished = 0;
    shared->clock.start = 0;
    if (pthread_mutex_init(&shared->state_lock, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&shared->print_lock, NULL) != 0)
    {
		pthread_mutex_destroy(&shared->state_lock);
		return (1);
	}
    shared->forks = malloc(sizeof(pthread_mutex_t) * shared->count);
    if (!shared->forks)
    {
        pthread_mutex_destroy(&shared->print_lock);
		pthread_mutex_destroy(&shared->state_lock);
		return (1);
	}
    shared->people = malloc(sizeof(t_person) * shared->count);
   if (!shared->people)
	{
		pthread_mutex_destroy(&shared->print_lock);
		pthread_mutex_destroy(&shared->state_lock);
        free(shared->forks);
		return (1);
	}
    if (init_forks(shared))
    {
        free(shared->people);
		free(shared->forks);
		pthread_mutex_destroy(&shared->print_lock);
		pthread_mutex_destroy(&shared->state_lock);
		return (1);
	}
    return (0);    
}