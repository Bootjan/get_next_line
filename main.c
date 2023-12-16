#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	char	*out = get_next_line(fd);
	while (out)
	{
		printf("%s$\n", out);
		free(out);
		out = get_next_line(fd);
	}
	close(fd);
	return (0);
}

