/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdere <hdere@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:05:00 by hdere             #+#    #+#             */
/*   Updated: 2026/05/14 18:47:10 by hdere            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digitt(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(char *str)
{
	long	result;
	int		i;

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

static int	fill_limit_arg(int ac, char **av, t_shared *shared)
{
	if (ac == 6)
	{
		shared->limit.active = 1;
		shared->limit.target = ft_atol(av[5]);
		if (shared->limit.target == -1)
			return (1);
	}
	else
	{
		shared->limit.active = 0;
		shared->limit.target = -1;
	}
	return (0);
}

static int	fill_shared_values(int ac, char **av, t_shared *shared)
{
	shared->count = ft_atol(av[1]);
	if (shared->count == -1)
		return (1);
	shared->clock.die = ft_atol(av[2]);
	if (shared->clock.die == -1)
		return (1);
	shared->clock.eatt = ft_atol(av[3]);
	if (shared->clock.eatt == -1)
		return (1);
	shared->clock.sleep = ft_atol(av[4]);
	if (shared->clock.sleep == -1)
		return (1);
	return (fill_limit_arg(ac, av, shared));
}

int	parse_args(int ac, char **av, t_shared *shared)
{
	if (ac != 5 && ac != 6)
		return (1);
	if (!is_digitt(av[1]) || !is_digitt(av[2])
		|| !is_digitt(av[3]) || !is_digitt(av[4]))
		return (1);
	if (ac == 6 && !is_digitt(av[5]))
		return (1);
	if (fill_shared_values(ac, av, shared))
		return (1);
	if (shared->count <= 0 || shared->clock.die <= 0
		|| shared->clock.eatt <= 0 || shared->clock.sleep <= 0)
		return (1);
	if (shared->limit.active && shared->limit.target <= 0)
		return (1);
	return (0);
}
