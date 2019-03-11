#include "printf.h"
#include "ft_ssl_md5.h"
#include "ssl_dispatch.h"

void			check_stdin(char **av, int ac, int dis)
{
	char			*file;
	int				len;
	int				j;
	int				k;
	int				flags;

	j = 0;
	k = 0;
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
			if (flags & s && av[j][k + 1])
				flags -= handle_string(av, ac, j, flags, dis);
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

void			do_ssl(int flags, char *input, int dis)
{
	char			*file;
	int				len;
	int				fd;

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
			ft_printf("%s (%s) = ", g_sslfun[dis].print, file);
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
	while (flags[++i])
	{
		while (g_sslflags[j].flag != flags[i])
			j++;
		if (!g_sslflags[j])
			return (-1);
		sum += g_sslflags[j].value;
		if (sum & s)
			return (sum);
	}
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

void			ssl_flags(char **av, int ac, int dis)
{
	unsigned char	flags;
	int				j;
	int				k;
	int				dis;

	j = -1;
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
			k = 1;
			if (av[j][k] == '-')
				k++;
			flags += flag_val(av[j] + k);
			if (flags == -1)
				flag_error(av[j], dis);
			if (flags & s)
				flags -= handle_string(av, j, flags, dis);
		}
		else if (av[j][0] != '-')
		{
			do_ssl(flags, av[j]);
			flags = 0; //verify that this resets otherwise make sure to remove s flag if necessary
		}
	}
}
