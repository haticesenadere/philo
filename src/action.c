#include "philo.h"

void    print_action(t_person *person, const char *action)
{
    long    timestamp;

    if (is_finished(person->shared))
    {
        return ;
    }
    pthread_mutex_lock(&person->shared->print_lock);
    if (!is_finished(person->shared))
    {
        timestamp = now_ms() - person->shared->clock.start;
        printf("%ld %d %s\n", timestamp, person->person_number, action);
    }
    pthread_mutex_unlock(&person->shared->print_lock);
}