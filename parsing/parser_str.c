#include "../includes/minishell.h"

char	*ft_slesh(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(str);
	free(tmp2);
	++(*i);
	return (tmp);
}

char	*ft_gap(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp4 = ft_strjoin(tmp, tmp2);
	free(tmp2);
	free(tmp);
	tmp = ft_strjoin(tmp4, tmp3);
	free(tmp3);
	free(tmp4);
	free(str);
	return (tmp);
}

char	*ft_gap2(char *str, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while ((str[++(*i)]))
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$' \
			|| str[*i + 1] == '\\'))
			str = ft_slesh(str, i);
		if (str[*i] == '$')
			str = ft_dollar(str, i, env);
		if (str[*i] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	free(str);
	str = ft_strjoin(tmp, tmp2);
	free(tmp);
	tmp = ft_strjoin(str, tmp3);
	free_str(str, tmp2, tmp3, NULL);
	return (tmp);
}

char	*ft_dollar(char *str, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
		if (!ifkey(str[*i]))
			break ;
	if (*i == j + 1)
		return (str);
	tmp = ft_substr(str, j + 1, *i - j - 1);
	if (ft_strcmp(tmp, "?") != 0)
	{
		tmp2 = ft_dollar_utils(tmp, i, env);
		tmp3 = ft_substr(str, 0, j);
		tmp3 = ft_strjoin_with_clean(tmp3, tmp2);
		tmp3 = ft_strjoin_with_clean(tmp3, ft_substr(str, *i, ft_strlen(str)));
		if (ft_strcmp(tmp2, "") == 0)
			*i = (*i) - ft_strlen(tmp) - 1;
	}
	else
		tmp3 = ft_itoa(g_status);
	free_str(str, NULL, tmp, NULL);
	//str = tmp3;
	return (tmp3);
}

char	*ft_insert_space_after_red(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*c;

	j = *i;
	c = ft_strdup(" ");

	if (str[j + 1] != '>' && str[j + 1] != '<' && str[j + 1] != ' ')
	{
		tmp = ft_substr(str, 0, (j + 1));
		tmp2 = ft_substr(str, (j + 1), (ft_strlen(str) - j));
		tmp = ft_strjoin(tmp, c);
		tmp = ft_strjoin(tmp, tmp2);
		free(str);
		free(c);
		*i = j + 2;
		return (tmp);
	}
	else
		return (str);
}

char	*parser_str(char *str, char **env)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = ft_gap(str, &i);
		if (str[i] == '\\')
			str = ft_slesh(str, &i);
		if (str[i] == '\"')
			str = ft_gap2(str, &i, env);
		if (str[i] == '$')
			str = ft_dollar(str, &i, env);
//		if (str[i] == '>' || str[i] == '<')
//			str = ft_insert_space_after_red(str, &i);
	}
	return (str);
}
