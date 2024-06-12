#include "libft.h"

double	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + time.tv_usec / 1000));
}
