#include "philo.h"

static void	write_number(long num, char *buf, int *idx)
{
	char	temp[20];
	int		i;
	int		j;

	if (num == 0)
	{
		buf[(*idx)++] = '0';
		return ;
	}
	i = 0;
	if (num < 0)
	{
		buf[(*idx)++] = '-';
		num = -num;
	}
	while (num > 0)
	{
		temp[i++] = (num % 10) + '0';
		num /= 10;
	}
	j = i - 1;
	while (j >= 0)
		buf[(*idx)++] = temp[j--];
}

static void	write_string(const char *str, char *buf, int *idx)
{
	while (*str)
		buf[(*idx)++] = *str++;
}

void    print_action(t_person *person, const char *action)
{
	char	buffer[256];
	int		idx;
	long	timestamp;

	pthread_mutex_lock(&person->shared->print_lock);
	if (!is_finished(person->shared))
	{
		idx = 0;
		timestamp = now_ms() - person->shared->clock.start;
		write_number(timestamp, buffer, &idx);
		buffer[idx++] = ' ';
		write_number(person->person_number, buffer, &idx);
		buffer[idx++] = ' ';
		write_string(action, buffer, &idx);
		buffer[idx++] = '\n';
		write(1, buffer, idx);
	}
	pthread_mutex_unlock(&person->shared->print_lock);
}

void    do_eat(t_person *person)
{
    if (is_finished(person->shared))
        return ;
    
    if (person->shared->limit.active && 
        get_eat_count(person) >= person->shared->limit.target)
        return ;
    
    get_forks(person);
    if (is_finished(person->shared))
    {
        release_forks(person);
        return ;
    }
    print_action(person, "has taken a fork");
    print_action(person, "has taken a fork");

    pthread_mutex_lock(&person->life.lock);
    person->life.last_eat = now_ms();
    pthread_mutex_unlock(&person->life.lock);

    print_action(person, "is eating");
    precise_sleep(person->shared->clock.eatt, person->shared);

    pthread_mutex_lock(&person->life.lock);
    if (!is_finished(person->shared))
        person->life.eat_count++;
    pthread_mutex_unlock(&person->life.lock);

    release_forks(person);
}

void    do_sleep(t_person *person)
{
    print_action(person, "is sleeping");
    precise_sleep(person->shared->clock.sleep, person->shared);
}

void    do_think(t_person *person)
{
    long    think_ms;

    print_action(person, "is thinking");
    think_ms = person->shared->clock.die
        - person->shared->clock.eatt
        - person->shared->clock.sleep;

    if (think_ms > 0)
    {
        if (person->shared->count % 2 == 0)
            precise_sleep(think_ms / 4, person->shared);
        else
            precise_sleep(think_ms / 2, person->shared);
    }
}
