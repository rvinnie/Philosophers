#include "philosophers.h"

int	check_argv(char *str_arg)
{
	unsigned int	num_arg;
	int				i;

	i = 0;
	num_arg = 0;
	while (str_arg[i])
	{
		if (str_arg[i] < '0' || str_arg[i] > '9')
			return (0);
		num_arg = num_arg * 10 + (str_arg[i] - '0');
		i++;
	}
	return (num_arg);
}

int	set_args(t_main *s_main, t_info *s_info, int argc, char *argv[])
{
	s_info->num_of_philos = check_argv(argv[1]);
	s_info->time_to_die = check_argv(argv[2]);
	s_info->time_to_eat = check_argv(argv[3]);
	s_info->time_to_sleep = check_argv(argv[4]);
	if (!s_info->num_of_philos || !s_info->time_to_die
		|| !s_info->time_to_eat || !s_info->time_to_sleep)
		return (-1);
	if (argc == 6)
	{
		s_main->num_must_eat = check_argv(argv[5]);
		if (!s_main->num_must_eat)
			return (-1);
	}
	else
		s_main->num_must_eat = -1;
	return (0);
}

int	init_philos(t_main *s_main, t_info *s_info)
{
	t_philo *s_philos;
	int		i;

	s_philos = malloc(sizeof(t_philo) * s_info->num_of_philos);
	if (!(s_philos))
		return (put_error("error: failed to allocate memory\n"));
	i = 0;
	while (i < s_info->num_of_philos)
	{
		s_philos[i].philo_num = i + 1;
		s_philos[i].left_fork = i;
		if (i == s_info->num_of_philos - 1)
			s_philos[i].right_fork = 0;
		else
			s_philos[i].right_fork = i + 1;
		s_philos[i].eat_count = 0;
		s_philos[i].s_info = s_info;
		i++;
	}
	s_main->s_philos = s_philos;
	return (0);
}

int	init_forks(t_info *s_info)
{
	pthread_mutex_t *forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * s_info->num_of_philos);
	if (!forks)
		return (put_error("error: failed to allocate memory\n"));
	i = 0;
	while (i < s_info->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (put_error("error: mutex is not initialized\n"));
		i++;
	}
	s_info->forks = forks;
	return (0);
}

void	eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->s_info->forks[philo->left_fork]);
	print_state(philo->s_info, philo->philo_num, "has taken a fork");
	pthread_mutex_lock(&philo->s_info->forks[philo->right_fork]);
	print_state(philo->s_info, philo->philo_num, "has taken a fork");
	print_state(philo->s_info, philo->philo_num, "is eating");
	usleep(philo->s_info->time_to_eat * 1000);
	philo->time_last_meal = get_cur_time(philo->s_info->start_time);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->s_info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->s_info->forks[philo->right_fork]);
}

void	*test_meal(void *s_philo)
{
	t_philo	philo;
	philo = *(t_philo *)s_philo;

	while (1 == 1)
	{
		print_state(philo.s_info, philo.philo_num, "is thinking");
		eating(&philo);
		print_state(philo.s_info, philo.philo_num, "is sleeping");
		usleep(philo.s_info->time_to_sleep * 1000);
	}	
}

int	start_philos(t_main *s_main, t_info *s_info)
{
	void	*s_philo;
	int	i;

	i = 0;
	s_info->start_time = get_cur_time(0);
	while (i < s_info->num_of_philos)
	{
		s_philo = (void *)(&s_main->s_philos[i]);
		if (pthread_create(&s_main->s_philos[i].philo, NULL, test_meal, s_philo))
			return (put_error("error: failed to create thread\n"));
		i++;
	}
	i = 0;
	while (i < s_info->num_of_philos)
	{
		if (pthread_join(s_main->s_philos[i].philo, NULL))
			return (put_error("error: failed to create thread\n"));
		i++;
	}
}

int main(int argc, char *argv[])
{
	int		status;
	t_main	s_main;
	t_info	s_info;

	if (argc < 5 || argc > 6)
		return (put_error("error: wrong number of arguments\n"));
	if (set_args(&s_main, &s_info, argc, argv) == -1)
		return (put_error("error: wrong argument values\n"));
	// printf("%d %d %d %d %d\n", s_main.num_of_philos, s_main.time_to_die, s_main.time_to_eat, s_main.time_to_sleep, s_main.num_must_eat);
	if (init_philos(&s_main, &s_info) || init_forks(&s_info))
		return (1);
	start_philos(&s_main, &s_info);
	return (0);
}