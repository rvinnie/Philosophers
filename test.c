#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
struct timeval tv;


typedef struct
{
	pthread_mutex_t	left;
	pthread_mutex_t	right;
	int	number;
}	t_philo;

void	print_state(t_philo s_philo, int status)
{
	char *state;

	if (status == 0)
		state = "is thinking";
	else if (status == 1)
		state = "is eating";
	else if (status == 2)
		state = "is sleeping";
	else if (status == 3)
		state = "has taken a fork";
	gettimeofday(&tv, NULL);
	printf("%-20ld %d %s\n", tv.tv_usec, s_philo.number, state);
}

void	*test_philo(void *structure)
{
	t_philo s_philo;
	int flag = 1;

	s_philo = *(t_philo *)structure;
	s_philo.left = mutex1;
	s_philo.right = mutex2;
	while (flag)
	{
		// gettimeofday(&tv, NULL);
		// printf("%-20ld %d is thinking\n", tv.tv_usec, s_philo.number);
		print_state(s_philo, 0);
		usleep(800000);
		pthread_mutex_lock(&s_philo.left);
		print_state(s_philo, 3);
		pthread_mutex_lock(&s_philo.right);
		print_state(s_philo, 3);
		print_state(s_philo, 0);
		usleep(200000);
		pthread_mutex_unlock(&s_philo.left);
		pthread_mutex_unlock(&s_philo.right);
		print_state(s_philo, 2);
		usleep(200000);
	}
}

int main()
{

	t_philo s_philo1;
	t_philo s_philo2;
	pthread_t t1;
	pthread_t t2;

	s_philo1.number = 1;
	s_philo2.number = 2;
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	pthread_create(&t1, NULL, test_philo, &s_philo1);
	pthread_create(&t1, NULL, test_philo, &s_philo2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}