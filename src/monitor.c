#include "philo.h"

static int check_death(t_shared *shared)
{
    int     i;
    long    elapsed;

    i = 0;
    while (i < shared->count)
    {
        elapsed = now_ms() - get_last_eat(&shared->people[i]);

        if (elapsed >= shared->clock.die)
        {
            print_action(&shared->people[i], "died");
            set_finished(shared);
            return (1);
        }
        i++;
    }
    return (0);
}

static int check_meal_limit(t_shared *shared)
{
    int     i;

    if (!shared->limit.active)
        return (0);
    i = 0;

    while (i < shared->count)
    {
        if (get_eat_count(&shared->people[i]) < shared->limit.target)
            return (0);
        i++;
    }
    return (1);
}




void    *monitor_routine(void *arg)
{
    t_shared    *shared;

    shared = (t_shared *)arg;
    while (!is_finished(shared))
    {
        if (check_death(shared))
            break ;
        if (check_meal_limit(shared))
        {
            set_finished(shared);
            break;
        }
        usleep(100);
    }
    return (NULL);
}
