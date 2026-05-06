#include "philo.h"

int main(int ac, char **av)
{
    t_shared    shared;

    if(parse_args(ac, av, &shared))
        return(write(2, "Error\n", 6), 1);
    if (init_shared(&shared))
        return(write(2, "Error\n", 6), 1);
    if (init_people(&shared))
    {
        clean_fork_locks(&shared, shared.count);
        free(shared.forks);
        free(shared.people);
        pthread_mutex_destroy(&shared.print_lock);
        pthread_mutex_destroy(&shared.state_lock);
        return(write(2, "Error\n", 6), 1);
    }
    if (simulation_start(&shared))
	    return (clean_shared(&shared), write(2, "Error\n", 6), 1);

    join_created_people(&shared, shared.count);
    clean_shared(&shared);
    return (0);
}