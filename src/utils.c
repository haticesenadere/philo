#include "philo.h"


long    now_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    precise_sleep(long ms, t_shared *shared)
{
    long    end;

    end = now_ms() + ms;

    while (!is_finished(shared) && now_ms() < end)
        usleep(500);

}

int     is_finished(t_shared *shared)
{
    int     finished;

    pthread_mutex_lock(&shared->state_lock);
    finished = shared->finished;

    pthread_mutex_unlock(&shared->state_lock);
    return (finished);
}

long    get_last_eat(t_person *person)
{
    long    last_eat;

    pthread_mutex_lock(&person->life.lock);
    last_eat = person->life.last_eat;
    pthread_mutex_unlock(&person->life.lock);
    return (last_eat);
}

int     get_eat_count(t_person *person)
{
    int     count;

    pthread_mutex_lock(&person->life.lock);
    count = person->life.eat_count;
    pthread_mutex_unlock(&person->life.lock);
    return (count);
}

void    set_finished(t_shared *shared)
{
    pthread_mutex_lock(&shared->state_lock);
    shared->finished = 1;
    pthread_mutex_unlock(&shared->state_lock);
}
