#include "philo.h"

static void birth_time(t_shared *shared )
{
    int i;

    i = 0;
    while (i < shared->count)
    {
        pthread_mutex_lock(&shared->people[i].life.lock);   
        shared->people[i].life.last_eat = shared ->clock.start;
        pthread_mutex_unlock(&shared->people[i].life.lock);   
        i++;
    }
}

static int wake_people(t_shared *shared)
{
    int     i;

    i = 0;
    while (i < shared->count)
    {
        if (pthread_create(&shared->people[i].tid, NULL, 
                person_routine, &shared->people[i]) != 0)
            return (i);
        i++;
    }
    return (-1);
}

void    join_created_people(t_shared *shared, int limit)
{
    int     i;

    i = 0;
    while (i < limit)
    {
        if (shared->people[i].tid != 0)
            pthread_join(shared->people[i].tid, NULL);
        i++;
    }
    
}

int simulation_start(t_shared *shared) 
{
    int     failed_at;
    pthread_t   monitor_tid;

    shared->clock.start = now_ms();
    birth_time(shared);
    failed_at = wake_people(shared);
    if (failed_at != -1)
    {
        set_finished(shared);
        join_created_people(shared, failed_at);
        return (1);
    }

    if (pthread_create(&monitor_tid, NULL, monitor_routine, shared) != 0)
    {
        set_finished(shared);
        join_created_people(shared, shared->count);
        return (1);
    }
    pthread_join(monitor_tid, NULL);
    join_created_people(shared, shared->count);
    return (0);
}
