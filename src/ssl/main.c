#include "printf.h"
#include "ft_ssl_md5.h"
#include "ssl_dispatch.h"

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

int				get_input(int flags, char *input, char **file)
{
	int				len;
	int				ret;
	int				fd;
	char			buf[BUFF_SIZE + 1];
	char			*file;

	if (flags & s)
	{
		*file = ft_strdup(input);
		return (ft_strlen(input));
	}
	file = ft_strnew(o);
	fd = open_file(input);
	len = 0;
	if (fd == -1)
		return (0);
	while ((ret = read(fd, file, BUFF_SIZE)) > 0)
	{
		file[ret] = '\0';
		file = swap_n_free(ft_strjoin(file, buf), &file);
		len += ret;
	}
	if (ret < 0)
	{
		free(file);
		return (0);
	}
	return (len);
}

void			do_ssl(int flags, char *input, int dis)
{
	char			*file;
	int				len;

	len = get_input(flags, input, &file);
	if (flags & p)
		ft_printf("%s\n", input);
	if (!(flags & q))
	{
		if (flags & r)
		{
		}
		else
		{
		}
	}
	else
}

void			ssl_flags(char **av, int ac)
{
	unsigned char	flags;
	int				i;
	int				j;
	int				k = 0;

	i = 0;
	j = 0;
	flags = 0;
	while (j < ac)
	{
		if (av[j][0] == '-')
		{
			k = 1;
			if (av[j][k] == '-')
				k++;
			while (g_sslflags[i].flag && av[2][1] != g_sslflags[i].flag)
				i++;
			flags += g_sslflags[i].value;
		}
		else if (av[j][0] != '-')
		{
			do_ssl(flags, av[j]);
			flags = 0; //verify that this resets
		}
		j++;
	}
	return (flags);
}

int				main(int ac, char **av)
{
	int				dis;
	int				flags;
	
	dis = 0;
	if (ac == 3)
	{
		while (g_sslfuns[dis].name && ft_strcmp(av[1], g_sslfuns[dis].name))
			dis++;
		flags = ssl_flags(av, dis);
		do_ssl(av, ac, dis, flags);
	}
	return (0);
}
