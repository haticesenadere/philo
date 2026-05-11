#include "philo.h"

void    get_forks(t_person *person)
{
    int     min_fork;
    int     max_fork;

    if (person->fork_one < person->fork_two)
    {
        min_fork = person->fork_one;
        max_fork = person->fork_two;
    }else
    {
        min_fork = person->fork_two;
        max_fork = person->fork_one;
    }
    pthread_mutex_lock(&person->shared->forks[min_fork]);
    pthread_mutex_lock(&person->shared->forks[max_fork]);
    
    
}

void    release_forks(t_person *person)
{
    int     min_fork;
    int     max_fork;

    if ()
    {
        /* code */
    }
    
}