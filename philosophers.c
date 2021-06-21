#include "philosophers.h"

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void	print_state(unsigned int num, char *state)
{
	// char *state;

	// if (status == 0)
	// 	state = "is thinking";
	// else if (status == 1)
	// 	state = "has taken a fork";
	// else if (status == 2)
	// 	state = "is eating";
	// else if (status == 3)
	// 	state = "is sleeping";
	printf("%-16ld %u %s\n", get_cur_time(), num, state);
}

// void	*test_philo(void *structure)
// {
// 	t_philo s_philo;
// 	int flag = 1;

// 	s_philo = *(t_philo *)structure;
// 	s_philo.left = mutex1;
// 	s_philo.right = mutex2;
// 	while (flag)
// 	{
// 		print_state(s_philo, 0);
// 		usleep(800000);
// 		pthread_mutex_lock(&s_philo.left);
// 		print_state(s_philo, 1);
// 		pthread_mutex_lock(&s_philo.right);
// 		print_state(s_philo, 1);
// 		print_state(s_philo, 2);
// 		usleep(200000);
// 		pthread_mutex_unlock(&s_philo.left);
// 		pthread_mutex_unlock(&s_philo.right);
// 		print_state(s_philo, 3);
// 		usleep(200000);
// 	}
// }



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

int	set_args(t_main *s_main, int argc, char *argv[])
{
	s_main->num_of_philos = check_argv(argv[1]);
	s_main->time_to_die = check_argv(argv[2]);
	s_main->time_to_eat = check_argv(argv[3]);
	s_main->time_to_sleep = check_argv(argv[4]);
	if (!s_main->num_of_philos || !s_main->time_to_die
		|| !s_main->time_to_eat || !s_main->time_to_sleep)
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

int	init_philos(t_main *s_main)
{
	t_philo *s_philos;
	int		i;

	s_philos = malloc(sizeof(t_philo) * s_main->num_of_philos);
	if (!(s_philos))
		return (put_error("error: failed to allocate memory\n"));
	i = 0;
	while (i < s_main->num_of_philos)
	{
		s_philos[i].philo_num = i + 1;
		s_philos[i].left_fork = i;
		if (i == s_main->num_of_philos - 1)
			s_philos[i].right_fork = 0;
		else
			s_philos[i].right_fork = i + 1;
		s_philos[i].eat_count = 0;
		i++;
	}
	s_main->s_philos = s_philos;
	return (0);
}

int	init_forks(t_main *s_main)
{
	pthread_mutex_t *forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * s_main->num_of_philos);
	if (!forks)
		return (put_error("error: failed to allocate memory\n"));
	i = 0;
	while (i < s_main->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (put_error("error: mutex is not initialized\n"));
		i++;
	}
	s_main->forks = forks;
	return (0);
}

void	*test_meal(void *s_philo)
{
	t_philo	philo;
	philo = *(t_philo *)s_philo;

	// while (1 == 1)
	// {
	// 	print_state(s_philo, 0);
	// 	usleep(800000);
	// 	pthread_mutex_lock(&s_philo.left);
	// 	print_state(s_philo, philo.philo_num);
	// 	pthread_mutex_lock(&s_philo.right);
	// 	print_state(s_philo, philo.philo_num);
	// 	print_state(s_philo, philo.philo_num);
	// 	usleep(200000);
	// 	pthread_mutex_unlock(&s_philo.left);
	// 	pthread_mutex_unlock(&s_philo.right);
	// 	print_state(s_philo, philo.philo_num);
	// 	usleep(200000);
	// }
	
}

void	start_philos(t_main *s_main)
{
	void	*s_philo;
	int	i;

	i = 0;
	while (i < s_main->num_of_philos)
	{
		s_philo = (void *)(&s_main->s_philos[i]);
		if (pthread_create(s_main->s_philos[i].philo, NULL, test_meal, s_philo))
			return (put_error("error: failed to create thread\n"));
		i++;
	}
	// i = 0;
	// while (i < s_main->num_of_philos)
	// {
	// 	if (pthread_join(s_main->s_philos[i].philo, NULL))
	// 		return (put_error("error: failed to create thread\n"));
	// 	i++;
	// }
}

int main(int argc, char *argv[])
{
	t_main	s_main;
	int		status;

	if (argc < 5 || argc > 6)
		return (put_error("error: wrong number of arguments\n"));
	if (set_args(&s_main, argc, argv) == -1)
		return (put_error("error: wrong argument values\n"));
	// printf("%d %d %d %d %d\n", s_main.num_of_philos, s_main.time_to_die, s_main.time_to_eat, s_main.time_to_sleep, s_main.num_must_eat);
	if (init_philos(&s_main) || init_forks(&s_main))
		return (1);
	start_philos(&s_main);
	// while (i < count)
	// {
	// 	init_philos(philos, i);
	// 	i++;
	// }
	// t_philo s_philo1;
	// t_philo s_philo2;
	// pthread_t t1;
	// pthread_t t2;

	// s_philo1.number = 1;
	// s_philo2.number = 2;
	// pthread_mutex_init(&mutex1, NULL);
	// pthread_mutex_init(&mutex2, NULL);
	// pthread_create(&t1, NULL, test_philo, &s_philo1);
	// pthread_create(&t1, NULL, test_philo, &s_philo2);
	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
	return (0);
}