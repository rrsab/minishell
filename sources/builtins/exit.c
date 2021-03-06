/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:49:48 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/27 18:08:11 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_num(char *code)
{
	int	i;
	int	sign;
	int	len;

	i = 0;
	sign = 0;
	if (code[i] == '+' || code[i] == '-')
	{
		if (code[i] == '-')
			sign = 1;
		i++;
	}
	if ((ft_strcmp(code + i, "9223372036854775807") > 0 && sign == 0)
		|| (ft_strcmp(code, "-9223372036854775808") > 0 && sign == 1))
		return (0);
	len = ft_strlen(code + i);
	while (code[i] && ft_isdigit(code[i]))
		i++;
	if (i == len + sign)
		return (1);
	return (0);
}

static int	check_exit(char *argv)
{
	if (!is_num(argv))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putendl_fd(": numeric argument required", 2);
		free(argv);
		return (255);
	}
	free(argv);
	return (ft_atoi(argv));
}

int	cmd_exit(char **argv, t_list **env_ms)
{
	int		i;
	int		code;

	(void)env_ms;
	ft_putendl_fd("exit", 1);
	if (!argv[1])
		exit(0);
	i = 1;
	while (argv[i])
		i++;
	if (i > 2 && is_num(argv[1]))
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_status = 1;
		return (1);
	}
	code = check_exit(argv[1]) % 256;
	exit(code);
}
