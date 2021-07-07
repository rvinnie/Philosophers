#include "philosophers.h"

int	eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->s_info->forks[philo->left_fork]);
	print_state(philo->s_info, philo->philo_num, PHILO_FORK);
	if (philo->s_info->num_of_philos == 1)
	{
		pthread_mutex_unlock(&philo->s_info->forks[philo->left_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->s_info->forks[philo->right_fork]);
	print_state(philo->s_info, philo->philo_num, PHILO_FORK);
	print_state(philo->s_info, philo->philo_num, PHILO_EAT);
	usleep(philo->s_info->time_to_eat * 1000);
	philo->time_last_meal = get_cur_time(philo->s_info->start_time);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->s_info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->s_info->forks[philo->right_fork]);
	return (0);
}

void	*start_meal(void *s_philo)
{
	t_philo	*philo;

	philo = (t_philo *)s_philo;
	if (philo->philo_num % 2 == 0)
		usleep(philo->s_info->time_to_eat * 1000);
	while (*philo->s_info->stop == 0)
	{
		print_state(philo->s_info, philo->philo_num, PHILO_THINK);
		if (eating((t_philo *)s_philo) == 1)
			return (NULL);
		print_state(philo->s_info, philo->philo_num, PHILO_SLEEP);
		usleep(philo->s_info->time_to_sleep * 1000);
	}
	return (NULL);
}

unsigned int	get_jump(unsigned int num_of_philos)
{
	unsigned int	jump;

	if (num_of_philos < 2)
		jump = -1;
	if (num_of_philos % 2 != 0)
		jump = num_of_philos - 1;
	else
		jump = num_of_philos - 2;
	return (jump);
}

int	join_philos(t_main *s_main, t_info *s_info)
{
	unsigned int	i;

	i = 0;
	while (i < s_info->num_of_philos)
	{
		if (pthread_join(s_main->s_philos[i].philo, NULL))
			return (put_error(ERROR_THREAD));
		i++;
	}
	return (0);
}

int	start_philos(t_main *s_main, t_info *s_info)
{
	void			*s_philo;
	unsigned int	i;

	s_info->start_time = get_cur_time(0);
	i = 0;
	while (i < s_info->num_of_philos)
	{
		s_philo = (void *)(&s_main->s_philos[i]);
		if (pthread_create(&s_main->s_philos[i].philo,
				NULL, start_meal, s_philo))
			return (put_error(ERROR_THREAD));
		i++;
	}
	check_death(s_main, s_info);
	if (join_philos(s_main, s_info))
		return (put_error(ERROR_DETACH));
	return (0);
}
