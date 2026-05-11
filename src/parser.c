#include "philo.h"

static int is_digitt(char *str)
{
    int i;

    i = 0;
    if (!str || str[0] == '\0')
        return (0);

    while(str[i])
    {
        if (str[i] < '0' && str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

static long ft_atol(char *str)
{
    long    result;
    int     i;

    result = 0;
    i = 0;
    while (str[i])
    {
        result = result * 10 + (str[i] - '0');
        if (result > 2147483647)
            return (-1);
        i++;
    }
    return (result);

}

int parse_args(int ac, char **av, t_shared *shared)
{

    if (ac != 5 && ac != 6)
        return (1);

    if (!is_digitt(av[1]) || !is_digitt(av[2])
        || !is_digitt(av[3]) || !is_digitt(av[4]))
        return (1);
    if (ac == 6 && ! is_digitt(av[5]))
        return (1);
    shared->count = ft_atol(av[1]);
    shared->clock.die = ft_atol(av[2]);
    shared->clock.eatt = ft_atol(av[3]);
    shared->clock.sleep = ft_atol(av[4]);
    if (ac == 6)
    {
        shared->limit.active = 1;
        shared->limit.target = ft_atol(av[5]);
    }
    else
    {
        shared->limit.active = 0;
        shared->limit.target = -1;
    }

    if (shared->count <= 0 || shared->clock.die <= 0
            || shared->count <= 0 || shared->clock.sleep <= 0)
        return (1);
    if (shared->limit.active && shared->limit.target <= 0)
        return (1);
    return (0);
}
