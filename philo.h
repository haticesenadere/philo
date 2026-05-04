#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_clock
{
	long	start;
	long	die;
	long	eatt;
	long	sleep;
}	t_clock;

typedef struct s_limit
{
	int	active;
	int	target;
}	t_limit;

typedef struct s_life
{
	long			last_eat;
	int				eat_count;
	pthread_mutex_t	lock;
}	t_life;

typedef struct s_shared	t_shared;

typedef struct s_philo_person
{
	int			person_number;
	int			fork_one;
	int			fork_two;
	pthread_t	tid;
	t_life		life;
	t_shared	*shared;
}	t_person;

struct s_shared
{
	int				count;
	int				finished;
	t_clock			clock;
	t_limit			limit;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_person		*people;
};

#endif