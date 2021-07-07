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
	s_info->time_to_live = check_argv(argv[2]);
	s_info->time_to_eat = check_argv(argv[3]);
	s_info->time_to_sleep = check_argv(argv[4]);
	*s_info->stop = 0;
	if (!s_info->num_of_philos || !s_info->time_to_live
		|| !s_info->time_to_eat || !s_info->time_to_sleep)
		return (put_error(ERROR_VAL_ARGS));
	if (s_info->num_of_philos > 300)
		return (put_error(ERROR_TOO_LONG));
	if (argc == 6)
	{
		s_main->num_must_eat = check_argv(argv[5]);
		if (!s_main->num_must_eat)
			return (put_error(ERROR_VAL_ARGS));
	}
	else
		s_main->num_must_eat = -1;
	return (0);
}

int	init_philos(t_main *s_main, t_info *s_info)
{
	t_philo			*s_philos;
	pthread_mutex_t	eat_and_dead;
	unsigned int	i;

	s_philos = malloc(sizeof(t_philo) * s_info->num_of_philos);
	if (!(s_philos))
		return (put_error(ERROR_ALLOCATE));
	i = 0;
	while (i < s_info->num_of_philos)
	{
		pthread_mutex_init(&eat_and_dead, NULL);
		s_philos[i].philo_num = i + 1;
		s_philos[i].left_fork = i;
		s_philos[i].time_last_meal = 0;
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
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * s_info->num_of_philos);
	if (!forks)
		return (put_error(ERROR_ALLOCATE));
	i = 0;
	while (i < s_info->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			free(forks);
			return (put_error(ERROR_MUTEX));
		}
		i++;
	}
	s_info->forks = forks;
	return (0);
}
