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

void    do_eat(t_person *person)
{
    get_forks(person);
    pthread_mutex_lock(&person->life.lock);
    person->life.last_eat = now_ms();
    pthread_mutex_unlock(&person->life.lock);

    print_action(person, "has taken a fork");
    print_action(person, "has taken a fork");

    print_action(person, "is eating");
    precise_sleep(person->shared->clock.eatt, person->shared);

    if (!is_finished(person->shared))
    {
        pthread_mutex_lock(&person->life.lock);
        person->life.eat_count++;
		pthread_mutex_unlock(&person->life.lock);
    }
    release_forks(person);
}

void    do_sleep(t_person *person)
{
    print_action(person, "is sleeping");
    precise_sleep(person->shared->clock.sleep, person->shared);
}

void    do_think(t_person *person)
{
    long    think_ms;

    print_action(person, "is_thinking");
    if(person->shared->count % 2 == 0)
        return ;
    think_ms = person->shared->clock.die;
        - person->shared->clock.eatt
        - person->shared->clock.sleep;
    
    if (think_ms > 0)
        precise_sleep(think_ms / 2, person->shared);
    
}
