/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/20 12:22:07 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    pretty_print_cmd_list(t_cmd *cmd_list)
{
    int i;
    int cmd_num = 1;

    if (!cmd_list)
    {
        printf("----------------------------------------\n");
        printf("|           Command List is Empty      |\n");
        printf("----------------------------------------\n");
        return;
    }

    // Traverse the linked list of commands
    while (cmd_list)
    {
        printf("\n.---------------------------------------.\n");
        printf("|               COMMAND %-3d             |\n", cmd_num++);
        printf(":---------------------------------------:\n");

        // Print the full command path
        printf("| %-12s: %s\n", "Command", cmd_list->cmd ? cmd_list->cmd : "(null)");
        printf(":---------------------------------------:\n");

        // Print the arguments (argv)
        if (cmd_list->argv && cmd_list->argv[0])
        {
            printf("| %-12s: [%s]\n", "argv[0]", cmd_list->argv[0]);
            i = 1;
            while (cmd_list->argv[i])
            {
                printf("| %-12s  [%s]\n", "", cmd_list->argv[i]);
                i++;
            }
        }
        else
        {
            printf("| %-12s: (empty)\n", "argv");
        }
        printf(":---------------------------------------:\n");

        // Print I/O file descriptors
        printf("| %-12s: %d\n", "stdin_", cmd_list->stdin_);
        printf("| %-12s: %d\n", "stdout_", cmd_list->stdout_);
        printf(":---------------------------------------:\n");
        
        // --- NEW SECTION for flags ---
        printf("| %-19s: %d\n", "Cmd Not Found Flag", cmd_list->cmd_not_found);
        printf("| %-19s: %d\n", "Should Not Execute Flag", cmd_list->should_not_execute); // Print as a positive condition
        printf(":---------------------------------------:\n");


        // Print heredoc list
        t_heredoc *current_heredoc = cmd_list->heredcs;
        if (current_heredoc)
        {
            int heredoc_num = 1;
            // Loop through each heredoc associated with this command
            while (current_heredoc)
            {
                printf("| Heredoc #%-2d\n", heredoc_num++);
                printf("|   %-10s: [%s]\n", "Delimiter", current_heredoc->heredoc_del ? current_heredoc->heredoc_del : "(null)");
                printf("|   %-10s: [%s]\n", "File", current_heredoc->heredoc_file ? current_heredoc->heredoc_file : "(null)");
                printf("|   %-10s: %d\n", "FD", current_heredoc->fd);
                
                current_heredoc = current_heredoc->next;
                // Add a sub-divider if there is another heredoc to print
                if (current_heredoc)
                {
                    printf(":.......................................:\n");
                }
            }
        }
        else
        {
            printf("| %-12s: (none)\n", "Heredocs");
        }

        printf("'---------------------------------------'\n");

        // Move to the next command in the list
        cmd_list = cmd_list->next;
    }
}


void	ft_parse(t_data *data)
{
	void	**args;
	t_cmd	*list;

	list = NULL;
	if (!syntax_checker(data) && !all_spaces(data->readline_in))
	{
		args = ft_tokenizer(data);
		if (args)
			list = exec_setup(args, data);
		if (list)
			heredoc(list);
		if (list)
			check_errors(list, (t_token **)args);
		if (list)
			execute(list, data);
	}
}

void	dup_to_redir(t_cmd *current)
{
	if (current->stdin_ != 0)
	{
		dup2(current->stdin_, STDIN_FILENO);
		close(current->stdin_);
	}
	if (current->stdout_ != 1)
	{
		dup2(current->stdout_, STDOUT_FILENO);
		close(current->stdout_);
	}
}

void	restore_std(t_data *data)
{
	dup2(data->stdin_, STDIN_FILENO);
	dup2(data->stdout_, STDOUT_FILENO);
}

int	cmd_verifier(t_cmd *data)
{
	t_cmd	*ptr;
	int		status;

	ptr = data;
	if (ft_strcmp(*ptr->argv, "cd") == 0)
		status = do_cd(data);
	else if (ft_strcmp(*ptr->argv, "echo") == 0)
		status = do_echo(data);
	else if (ft_strcmp(*ptr->argv, "env") == 0)
		status = do_env(data);
	else if (ft_strcmp(*ptr->argv, "exit") == 0)
		status = do_exit(data);
	else if (ft_strcmp(ptr->cmd, "export") == 0)
		status = do_export(data);
	else if (ft_strcmp(*ptr->argv, "pwd") == 0)
		status = do_pwd(data);
	else if (ft_strcmp(*ptr->argv, "unset") == 0)
		status = do_unset(data);
	else
		status = 0;
	return (status);
}

int	ft_builtin(t_cmd *data)
{
	int		status;

	status = 0;
	if (data->should_not_execute)
		return (1337);
	if ((!data || !data->argv))
		return (0);
	if (is_a_builtin(data->cmd))
	{
		dup_to_redir(data);
		status = cmd_verifier(data);
		restore_std(data->data);
	}
	return (status);
}
