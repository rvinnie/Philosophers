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

int	start_philos(t_main *s_main, t_info *s_info)
{
	void			*s_philo;
	unsigned int	i;

	i = 0;
	s_info->start_time = get_cur_time(0);
	while (i < s_info->num_of_philos)
	{
		s_philo = (void *)(&s_main->s_philos[i]);
		if (pthread_create(&s_main->s_philos[i].philo, NULL, start_meal, s_philo))
			return (put_error(ERROR_THREAD));
		i++;
	}
	check_death(s_main, s_info);
	i = 0;
	while (i < s_info->num_of_philos)
	{
		if (pthread_join(s_main->s_philos[i].philo, NULL))
			return (put_error(ERROR_THREAD));
		i++;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_main	s_main;
	t_info	s_info;

	if (argc < 5 || argc > 6)
		return (put_error(ERROR_NUM_ARGS));
	if (set_args(&s_main, &s_info, argc, argv) == -1)
		return (put_error(ERROR_VAL_ARGS));
	// printf("%d %d %d %d %d\n", s_main.num_of_philos, s_main.time_to_die, s_main.time_to_eat, s_main.time_to_sleep, s_main.num_must_eat);
	if (init_philos(&s_main, &s_info) || init_forks(&s_info))
		return (1);
	start_philos(&s_main, &s_info);
	return (0);
}
