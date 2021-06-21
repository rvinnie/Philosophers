#include "philosophers.h"


int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	put_error(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

long	get_cur_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

