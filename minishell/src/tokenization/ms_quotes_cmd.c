/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:11:17 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/16 18:03:41 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_len_args(char *value)
{
	int	len;
	int	i;
	int	quote;

	len = 1;
	i = 0;
	quote = 0;
	ms_skip_whitespaces(&i, value);
	while (value[i])
	{
		if (ms_is_quote(value[i]) && !quote)
			quote = value[i];
		else if (ms_is_quote(value[i]) && quote == value[i])
			quote = 0;
		if (ms_isspace(value[i]) && quote == 0)
		{
				len++;
				i++;
				ms_skip_whitespaces(&i, value);
				continue;
		}
		i++;
	}
	return (len);
}

int	ms_len_arg(char *value, int *i)
{
	int len;
	int	quote;
	int	x;

	quote = 0;
	ms_skip_whitespaces(i, value);
	x = (*i);
	while (value[x])
	{
		if(ms_is_quote(value[x]) && !quote)
			quote = value[x];
		else if (ms_is_quote(value[x]) && quote == value[x])
			quote = 0;
		if ((ms_isspace(value[x]) || ms_ismetachar(value[x])) && quote == 0)
				break ;
		x++;
	}
	len = x - (*i);
	return (len);
}

char	 *ms_put_args(char *value,int *i)
{
	int		quote;
	char	*arg;
	int		x;

	x = 0;
	quote = 0;
	arg = malloc(ms_len_arg(value, i) + 1);
	if (!arg)
		return NULL;
	ms_skip_whitespaces(i, value);
	while (value[*i])
	{
		if (ms_is_quote(value[*i]) && !quote)
			quote = value[*i];
		else if (ms_is_quote(value[*i]) && quote == value[*i])
			quote = 0;
		if ((ms_isspace(value[*i]) || ms_ismetachar(value[*i])) && quote == 0)
			break ;
		arg[x] = value[*i];
		x++;
		(*i)++;
	}
	arg[x] = '\0';
	return (arg);
}

t_token	*ms_quotes_cmd(t_token *token)
{
	char	**args;
	int		i;
	int		x;
	
	x = 0;
	i = 0;
	args = malloc(sizeof(char*) * (ms_len_args(token->value) + 1));
	if (!args)
		return NULL;
	while (token->value[i])
	{
		args[x] = ms_put_args(token->value, &i);
		x++;
	}
	args[x] = NULL;
	x = 0;
	while (args[x])
	{
		args[x] = ms_quotes_off(args[x]);
		x++;
	}
	token->args = args;
	return (token);
}

	// i = 0;
	// while (token->args[i])
	// {
	// 	printf("arg[%d]: %s\n", i, token->args[i]);
	// 	i++;
	// }