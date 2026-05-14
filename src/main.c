/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdere <hdere@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:03:27 by hdere             #+#    #+#             */
/*   Updated: 2026/05/14 18:47:02 by hdere            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_shared	shared;

	if (parse_args(ac, av, &shared))
		return (write(2, "Error\n", 6), 1);
	if (init_shared(&shared))
		return (write(2, "Error\n", 6), 1);
	if (init_people(&shared))
	{
		clean_fork_locks(&shared, shared.count);
		free(shared.forks);
		free(shared.people);
		pthread_mutex_destroy(&shared.print_lock);
		pthread_mutex_destroy(&shared.state_lock);
		return (write(2, "Error\n", 6), 1);
	}
	if (simulation_start(&shared))
		return (clean_shared(&shared), write(2, "Error\n", 6), 1);
	clean_shared(&shared);
	return (0);
}
