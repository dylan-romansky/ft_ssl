#include "printf.h"
#include "ft_ssl_md5.h"
#include "ssl_dispatch.h"

void			do_ssl(int flags, char *input, int dis)
{
	char			*file;
	int				len;

	len = get_input(open(input, O_RDONLY), flags, input, &file);
	if (!(flags & q))
	{
		if (flags & r)
		{
			g_sslfuns[dis].hash(input, len);
			ft_printf(" %s", input);
		}
		else
		{
			ft_printf("%s (%s) = ", g_sslfuns[dis].print, file);
			g_sslfuns[dis].hash(file, len);
		}
	}
	else
		g_sslfuns[dis].hash(file, len);
	ft_printf("\n");
}

int				flag_val(char *flags)
{
	int				i;
	int				j;
	int				sum;

	i = -1;
	j = 0;

	if (flags[0] == '-')
		i++;
	while (flags[++i])
	{
		while (g_sslflags[j].flag != flags[i])
			j++;
		if (!g_sslflags[j].flag)
			return (-1);
		sum += g_sslflags[j].value;
		if (sum & s)
			return (sum);
	}
	return (sum);
}

void			check_stdin(char **av, int ac, int dis)
{
	char			*file;
	int				len;
	int				j;
	int				flags;

	j = 2;
	flags = 0;
	while (j < ac)
	{
		if (av[j][0] == '-')
		{
			flags += flag_val(av[j] + 1);
			if (flags == -1)
				flag_error(g_sslfuns[dis].print);
		}
		else
			break ;
		j++;
	}
	len = get_input(0, flags, NULL, &file);
	if (len)
	{
		if (flags & p)
			ft_printf("%s\n", file);
		g_sslfuns[dis].hash(file, len);
		ft_printf("\n");
	}
}

int				handle_string(char **av, int ac, int j, int flags, int dis)
{
	int			i;

	i = 0;
	printf("here\n");
	while (av[j][i] != 's')
		i++;
	if (av[j][i + 1])
	{
		do_ssl(flags, av[j] + i + 1, dis);
		return (0);
	}
	else if (j + 1 < ac)
		do_ssl(flags, av[j + 1], dis);
	return (1);
}

void			ssl_flags(char **av, int ac)
{
	char			flags;
	int				j;
	int				dis;

	j = 1;
	flags = 0;
	dis = 0;
	while (g_sslfuns[dis].name && ft_strcmp(av[1], g_sslfuns[dis].name))
		dis++;
	if (!g_sslfuns[dis].name)
		error_nodis();
	check_stdin(av, ac, dis);
	while (++j < ac)
	{
		if (av[j][0] == '-')
		{
			flags += flag_val(av[j]);
			if (flags == -1)
				flag_error(av[j]);
			if (flags & s)
			{
				j += handle_string(av, ac, j, flags, dis);
				flags -= s;
			}
		}
		else if (av[j][0] != '-')
		{
			do_ssl(flags, av[j], dis);
			flags = 0; //verify that this resets otherwise make sure to remove s flag if necessary
		}
	}
}
