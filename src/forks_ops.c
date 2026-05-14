/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdere <hdere@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:07:31 by hdere             #+#    #+#             */
/*   Updated: 2026/05/14 18:46:45 by hdere            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_person *person)
{
	int	min_fork;
	int	max_fork;

	if (person->fork_one < person->fork_two)
	{
		min_fork = person->fork_one;
		max_fork = person->fork_two;
	}
	else
	{
		min_fork = person->fork_two;
		max_fork = person->fork_one;
	}
	pthread_mutex_lock(&person->shared->forks[min_fork]);
	pthread_mutex_lock(&person->shared->forks[max_fork]);
}

void	release_forks(t_person *person)
{
	int	min_fork;
	int	max_fork;

	if (person->fork_one < person->fork_two)
	{
		min_fork = person->fork_one;
		max_fork = person->fork_two;
	}
	else
	{
		min_fork = person->fork_two;
		max_fork = person->fork_one;
	}
	pthread_mutex_unlock(&person->shared->forks[max_fork]);
	pthread_mutex_unlock(&person->shared->forks[min_fork]);
}
