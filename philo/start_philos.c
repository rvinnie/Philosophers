#include "philosophers.h"

void	eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->s_info->forks[philo->left_fork]);
	print_state(philo->s_info, philo->philo_num, PHILO_FORK);
	pthread_mutex_lock(&philo->s_info->forks[philo->right_fork]);
	print_state(philo->s_info, philo->philo_num, PHILO_FORK);
	print_state(philo->s_info, philo->philo_num, PHILO_EAT);
	usleep(philo->s_info->time_to_eat * 1000);
	philo->time_last_meal = get_cur_time(philo->s_info->start_time);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->s_info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->s_info->forks[philo->right_fork]);
}

void	*start_meal(void *s_philo)
{
	t_philo	*philo;

	philo = (t_philo *)s_philo;
	while (1 == 1)
	{
		print_state(philo->s_info, philo->philo_num, PHILO_THINK);
		eating(philo);
		print_state(philo->s_info, philo->philo_num, PHILO_SLEEP);
		usleep(philo->s_info->time_to_sleep * 1000);
	}
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

int	detach_philos(t_main *s_main, t_info *s_info)
{
	unsigned int	i;

	i = 0;
	while (i < s_info->num_of_philos)
	{
		if (pthread_detach(s_main->s_philos[i].philo))
			return (1);
		i++;
	}
	return (0);
}

int	start_philos(t_main *s_main, t_info *s_info)
{
	void			*s_philo;
	unsigned int	jump;
	unsigned int	i;

	jump = get_jump(s_info->num_of_philos);
	s_info->start_time = get_cur_time(0);
	i = 0;
	while (i < s_info->num_of_philos)
	{
		s_philo = (void *)(&s_main->s_philos[i]);
		if (pthread_create(&s_main->s_philos[i].philo,
				NULL, start_meal, s_philo))
			return (put_error(ERROR_THREAD));
		usleep(1000);
		if (i == jump)
			i = 1;
		else
			i += 2;
	}
	if (detach_philos(s_main, s_info))
		return (put_error(ERROR_DETACH));
	check_death(s_main, s_info);
	return (0);
}
