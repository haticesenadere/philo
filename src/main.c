#include "philo.h"
int main(int ac, char **av)
{
    t_shared    shared;

    if(parse_args(ac, av, &shared))
        return(write(2, "Error\n", 6), 1);
    if (init_shared(&shared))
        return(write(2, "Error\n", 6), 1);
    if (init_people(&shared))
        return(write(2, "Error\n", 6), 1);
    

    return (0);
}