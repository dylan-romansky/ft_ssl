#include "ft_ssl_md5.h"

unsigned		flip_end(unsigned n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

unsigned long	flip_end_512(unsigned long n)
{
	return ((n >> 56) | ((n & 0xff000000000000) >> 40) |
			((n & 0xff0000000000) >> 24) | ((n & 0xff00000000) >> 8) |
			((n & 0xff000000) << 8) | ((n & 0xff0000) << 24) |
			((n & 0xff00) << 40) | (n << 56));
}

int				get_input(int fd, int flags, char *input, char **file)
{
	int				len;
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*content;

	if (flags & s)
	{
		*file = ft_strdup(input);
		return (ft_strlen(input));
	}
	content = ft_strnew(0);
	len = 0;
	if (fd == -1)
		return (0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		content = swap_n_free(ft_strjoin(content, buf), &content);
		len += ret;
	}
	if (ret < 0)
	{
		free(content);
		*file = NULL;
		return (0);
	}
	return (len);
}

int				handle_string(char **av, int j, int flags, int dis)
{
	int			i;
	char		*file;

	i = 0;
	while (av[j][i] != 's')
		i++;
	if (av[j][i + 1])
		get_input(0, flags, av[j] + i + 1, &file);
	else
		get_input(0, flags, av[j + 1], &file);
	g_sslfuns[dis].hash(file, ft_strlen(file));
	return (s);
}
