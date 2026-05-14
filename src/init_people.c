/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_people.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdere <hdere@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:04:40 by hdere             #+#    #+#             */
/*   Updated: 2026/05/14 18:46:53 by hdere            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_people_locks(t_shared *shared, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		pthread_mutex_destroy(&shared->people[i].life.lock);
		i++;
	}
}

int	init_people(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->count)
	{
		shared->people[i].person_number = i + 1;
		shared->people[i].fork_one = i;
		shared->people[i].fork_two = (i + 1) % shared->count;
		shared->people[i].tid = 0;
		shared->people[i].life.last_eat = 0;
		shared->people[i].life.eat_count = 0;
		shared->people[i].shared = shared;
		if (pthread_mutex_init(&shared->people[i].life.lock, NULL) != 0)
		{
			clear_people_locks(shared, i);
			return (1);
		}
		i++;
	}
	return (0);
}
