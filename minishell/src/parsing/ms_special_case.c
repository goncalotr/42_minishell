/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_special_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:48:40 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/13 19:48:43 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	ms_size_cmd(char *value)
// {
// 	int	i;
// 	int	quote;
// 	int	len; 

// 	len = 0;
// 	quote = 0;
// 	i = 0;
// 	while (value[i])
// 	{
// 		if (value[i] == '\'' || value[i] == '\"')
// 		{
// 			if (quote == 0)
// 			{
// 				quote = value[i++];
// 				continue;
// 			}
// 			else if (quote == value[i])
// 			{
// 				if (ms_isspace(value[i + 1]) || !value[i + 1])
// 					break;
// 				quote = 0;
// 				i++;
// 				continue;
// 			}
// 		}
// 		len++;
// 		i++;
// 	}
// 	if (len == 0)
// 		return (ms_size_cmd(&value[i]));
// 	return (len);
// }

// char	*ms_extract_cmd(char *value, char *cmd)
// {
// 	int	i;
// 	int	quote;
// 	int	k;
	
// 	k = 0;
// 	quote = 0;
// 	i = 0;
// 	while (value[i])
// 	{
// 		if (value[i] == '\'' || value[i] == '\"')
// 		{
// 			if (quote == 0)
// 			{
// 				quote = value[i++];
// 				continue;
// 			}
// 			else if (quote == value[i])
// 			{
// 				if (ms_isspace(value[i + 1]))
// 					break;
// 				quote = 0;
// 				i++;
// 				continue;
// 			}
// 		}
// 		cmd[k++] = value[i++];
// 	}
// }

// char 	**ms_special_case(t_token **token)
// {
// 	int		new_size;
// 	char	*cmd;

// 	new_size = ms_size_cmd((*token)->value);
// 	printf("size_cmd: %d\n", new_size);
// 	cmd = malloc(new_size + 1);
// 	if (!cmd)
// 		return NULL;	
// 	cmd = ms_extract_cmd((*token)->value, cmd);
// 	return NULL;
// }









































// {
// 	char	**args;
// 	char	**args_2;
// 	char	*str_1;
// 	char	*str_2;
// 	int		i;

// 	i = 0;
// 	args = ft_split((*token)->value, (*token)->value[0]);
// 	str_1 = ft_strdup(args[0]);
// 	str_2 = malloc(ms_len_array_strs(args) + 1);
// 	if (!str_2)
// 		return NULL;
// 	str_2 = ms_cpy_array(str_2, args);
// 	ms_free_array(args);
// 	args = ft_split(str_2, ' ');
// 	args_2 = malloc((ms_array_len(args) + 2) * sizeof(char *));
// 	args_2[0] = str_1;
// 	while (args[i])
// 	{
// 		args_2[i + 1] = ft_strdup(args[i]);
// 		i++;
// 	}
// 	args_2[i + 1] = NULL;
// 	free(args);
// 	return (args_2);
// }

// void	ms_free_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	if (!array)
// 		return ;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

// int		ms_len_array_strs(char **strs)
// {
// 	int i;
// 	int k;
// 	int len;

// 	i = 1;
// 	len = 0;
// 	while (strs[i])
// 	{
// 		k = 0;
// 		while (strs[i][k])
// 		{
// 			len++;
// 			k++;
// 		}
// 		i++;
// 	}
// 	return (len);
// }

// char	*ms_cpy_array(char *str, char **strs)
// {
// 	int i;
// 	int k;
// 	int y;

// 	i = 1;
// 	y = 0;
// 	while (strs[i])
// 	{
// 		k = 0;
// 		while (strs[i][k])
// 		{
// 			str[y] = strs[i][k];
// 			y++;
// 			k++;
// 		}
// 		i++;
// 	} 
// 	str[y] = '\0';
// 	return (str);
// }

// int	ms_array_len(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i])
// 		i++;
// 	return (i);	
// }
