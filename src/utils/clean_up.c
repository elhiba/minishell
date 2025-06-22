

#include "../../includes/minishell.h"

void	full_cleanup(t_data *data)
{
	if (!data)
		return ;
	free(data->readline_in);
	free_d_arr(data->env);
	free_cmd_list(&data->cmd_list);
	data->readline_in = NULL;
	data->env = NULL;
	data->cmd_list = NULL;
}

void	free_token_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->arg);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_cmd_list(t_cmd **head)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free_token_list(&current->list);
		if (current->in_fd > 2)
			close(current->in_fd);
		if (current->out_fd > 2)
			close(current->out_fd);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_d_arr(char **arr)
{
	char	**ptr;
	int		i;

	ptr = arr;
	i = 0;
	while (arr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
