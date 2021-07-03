#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	put_error(char *err)
{
	printf("error: %s\n", err);
	return (1);
}

long	get_cur_time(long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

void	print_state(t_info *s_info, unsigned int num, char *state)
{
	long	start_time;

	start_time = s_info->start_time;
	if (!s_info->stop)
		printf("%-10ld %u %s\n", get_cur_time(start_time), num, state);
}
