/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdere <hdere@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:08:45 by hdere             #+#    #+#             */
/*   Updated: 2026/05/14 18:46:42 by hdere            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_people_locks(t_shared *shared, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		pthread_mutex_destroy(&shared->people[i].life.lock);
		i++;
	}
}

void	clean_fork_locks(t_shared *shared, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		i++;
	}
}

void	clean_shared(t_shared *shared)
{
	if (shared->people)
	{
		clean_people_locks(shared, shared->count);
		free(shared->people);
		shared->people = NULL;
	}
	if (shared->forks)
	{
		clean_fork_locks(shared, shared->count);
		free(shared->forks);
		shared->forks = NULL;
	}
	pthread_mutex_destroy(&shared->print_lock);
	pthread_mutex_destroy(&shared->state_lock);
}
