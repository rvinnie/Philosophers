#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct
{
	long			start_time;
	pthread_mutex_t	*forks;
	unsigned int	num_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
}	t_info;

typedef struct
{
	pthread_t		philo;
	unsigned int	philo_num;
	unsigned int	left_fork;
	unsigned int	right_fork;
	unsigned int	eat_count;
	long			time_last_meal;
	t_info			*s_info;
}	t_philo;

typedef struct
{
	t_philo			*s_philos;
	unsigned int	num_must_eat;
}	t_main;


int		ft_strlen(char *str);
int		put_error(char *err);
long	get_cur_time(long start_time);
void	print_state(t_info *s_info, unsigned int num, char *state);