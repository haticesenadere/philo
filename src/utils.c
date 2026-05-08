#include "philo.h"



long    get_last_eat(t_person *person)
{
    long    last_eat;

    pthread_mutex_lock(&person->life.lock);
    last_eat = person->life.last_eat;
    pthread_mutex_unlock(&person->life.lock);
    return (last_eat);
}

void    set_finished(t_shared *shared)
{
    pthread_mutex_lock(&shared->state_lock);
    shared->finished = 1;
    pthread_mutex_unlock(&shared->state_lock);
}

int     get_eat_count(t_person *person)
{
    int     count;

    pthread_mutex_lock(&person->life.lock);
    count = person->life.eat_count;
    pthread_mutex_unlock(&person->life.lock);
    return (count);
}