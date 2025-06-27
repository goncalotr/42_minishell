/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:57:22 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/06/27 20:37:52 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



// Helper to get a string name for a token type enum.
static const char *get_type_str(t_token_type type)
{
    if (type == TOKEN_INFILE) return "INFILE";
    if (type == TOKEN_OUTFILE) return "OUTFILE";
    if (type == TOKEN_CMD) return "CMD";
    if (type == TOKEN_PIPE) return "PIPE";
    if (type == TOKEN_REDIR_IN) return "REDIR_IN";
    if (type == TOKEN_REDIR_OUT) return "REDIR_OUT";
    if (type == TOKEN_APPEND) return "APPEND";
    if (type == TOKEN_HEREDOC) return "HEREDOC";
    if (type == TOKEN_EOF) return "EOF";
    return "UNKNOWN";
}

/**
 * @brief Prints the entire token list for debugging purposes.
 *        Displays the value, type, and args array for each node.
 *
 * @param list The head of the token list to print.
 * @param stage_name A string describing when this print is happening
 *                   (e.g., "After Tokenization", "After Expansion").
 */
void ms_debug_print_tokens(t_token *list, const char *stage_name)
{
    int i = 0;
    t_token *current = list;

    // Use different colors to make the debug output stand out.
    ft_printf(CYAN "\n=============== TOKEN LIST DEBUG (%s) ===============\n" RESET, stage_name);
    if (!current)
    {
        ft_printf(YELLOW "Token list is empty.\n" RESET);
        ft_printf(CYAN "========================================================\n\n" RESET);
        return;
    }

    while (current)
    {
        ft_printf(BLUE "--- Node %d ---\n" RESET, i);
        ft_printf(WHITE "  Type  : %s\n" RESET, get_type_str(current->type));

        if (current->value)
        {
            ft_printf(WHITE "  Value : \"%s\"\n" RESET, current->value);
        }
        else
        {
            ft_printf(YELLOW "  Value : (null)\n" RESET);
        }

        if (current->args)
        {
            ft_printf(WHITE "  Args[]:\n" RESET);
            int j = 0;
            while (current->args[j])
            {
                ft_printf(GREEN "    -> arg[%d]: \"%s\"\n" RESET, j, current->args[j]);
                j++;
            }
            if (j == 0)
            {
                 ft_printf(YELLOW "    (args array is allocated but empty)\n" RESET);
            }
        }
        else
        {
            ft_printf(YELLOW "  Args[]: (null)\n" RESET);
        }
        
        current = current->next;
        i++;
    }
    ft_printf(CYAN "========================================================\n\n" RESET);
}




int	ms_len_token(char *input, int i)
{
	int	len;
	int	quote;
	int	x;

	quote = 0;
	x = i;
	while (input[x])
	{
		if (ms_is_quote(input[x]) && !quote)
			quote = input[x];
		else if (ms_is_quote(input[x]) && quote == input[x])
			quote = 0;
		if (ms_ismetachar(input[x]) && quote == 0)
			break ;
		x++;
	}
	len = x - i;
	return (len);
}

char	*ms_cpy_token(char *input, int *i)
{
	char	*token;
	int		x;
	int		quote;

	quote = 0;
	x = 0;
	ms_skip_whitespaces(i, input);
	token = malloc(ms_len_token(input, *i) + 1);
	if (!token)
		return (NULL);
	while (input[*i])
	{
		if (ms_is_quote(input[*i]) && !quote)
			quote = input[*i];
		else if (ms_is_quote(input[*i]) && quote == input[*i])
			quote = 0;
		if ((ms_isspace(input[*i]) || ms_ismetachar(input[*i])) && quote == 0)
			break ;
		token[x] = input[*i];
		(*i)++;
		x++;
	}
	token[x] = '\0';
	return (token);
}

char	*ms_cpy_token_cmd(char *input, int *i)
{
	char	*token;
	int		x;
	int		quote;

	quote = 0;
	x = 0;
	ms_skip_whitespaces(i, input);
	token = malloc(ms_len_token(input, *i) + 1);
	if (!token)
		return (NULL);
	while (input[*i])
	{
		if (ms_is_quote(input[*i]) && !quote)
			quote = input[*i];
		else if (ms_is_quote(input[*i]) && quote == input[*i])
			quote = 0;
		if (ms_ismetachar(input[*i]) && quote == 0)
			break ;
		token[x] = input[*i];
		(*i)++;
		x++;
	}
	token[x] = '\0';
	return (token);
}

t_token	*ms_start_tokenization(char *input, t_token *list)
{
	int	i;

	i = 0;
	input = ms_remove_whitespaces(input);
	while (input[i])
	{
		ms_skip_whitespaces(&i, input);
		if ((input[i] == '|') || (input[i] == '<' || input[i] == '>'))
			list = ms_extract_operator(input, &i, list);
		else
			list = ms_extract_word(input, &i, list);
	}
	free(input);
	return (list);
}

t_token	*ms_tokenization(t_minishell *data, char *input)
{
	t_token		*tokens;
	t_token		*temp;

	tokens = NULL;
	tokens = ms_start_tokenization(input, tokens);
	tokens = ms_join_cmd(tokens);
	// ms_print_tokens(tokens);
	tokens = ms_expansion_check(tokens);
	tokens = ms_expand_variables(data, tokens);
	temp = tokens;
	while (temp)
	{
		if (temp->expand_index)
			free(temp->expand_index);
		temp = temp->next;
	}
	tokens = ms_handle_quotes(tokens);
	return (tokens);
}
