#include "philo.h"
static int  is_single_philosopher(t_person *person)
{
    return (person->shared->count == 1);
}

static void     *handle_single_philosopher(t_person *person)
{
    pthread_mutex_lock(&person->shared->forks[person->fork_one]);
    print_action(person, "has taken a fork");
    precise_sleep(person->shared->clock.die, person->shared);
    print_action(person, "died");
    set_finished(person->shared);
    pthread_mutex_unlock(&person->shared->forks[person->fork_one]);
    return (NULL);
}
static void philosopher_loop(t_person *person)
{
    while (!is_finished(person->shared))
    {
        do_eat(person);
        if (is_finished(person->shared))
            break ;
        do_sleep(person);
        if (is_finished(person->shared))
            break ;
        do_think(person);
    }
}

void    *person_routine(void *arg)
{
    t_person    *person;

    person = (t_person *)arg;

    if (is_single_philosopher(person))
        return (handle_single_philosopher(person));
    if (person->person_number % 2 == 1)
        usleep(5000);
    philosopher_loop(person);

    return (NULL);

}