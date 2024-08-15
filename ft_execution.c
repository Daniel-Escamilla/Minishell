/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:25:25 by user              #+#    #+#             */
/*   Updated: 2024/08/15 14:35:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_setvalues(t_cmd *cmd, t_mini *mini)
{
	cmd->names->index = 0;

	cmd->names->fd = 0;
	
	cmd->names->proc = ft_calloc(sizeof(int), mini->flags->pipe + 1);

}
	

void	ft_execute(t_cmd *cmd, t_mini *mini)
{
	execve(cmd->cmd, cmd->args, mini->env->env);
}

void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	if (pipe(cmd->names->fd_pipe) == -1)
		ft_error_bonus("Pipe Error", 1);
	cmd->names->proc[cmd->names->index] = fork();
	if (cmd->names->proc[cmd->names->index] == -1)
		ft_error_bonus("Failed in Fork()", 1);
	if (cmd->names->proc[cmd->names->index] == 0)
	{
		cmd->names->fd_infile = 
		
		cmd->names->fd_outfile = 

		close(cmd->names->fd_pipe[0]);
		dup2(cmd->names->fd_tmp, STDIN_FILENO);
		dup2(cmd->names->fd_pipe[1], STDOUT_FILENO);
		close(cmd->names->fd_tmp);
		close(cmd->names->fd_pipe[1]);
		ft_execute(cmd, mini);
	}
	cmd->names->fd_tmp = cmd->names->fd_pipe[0];
	cmd->names->index++;
	close(cmd->names->fd_pipe[1]);
}


int	ft_wait_bonus(t_cmd *cmd)
{
	int	state;
	int i;

	i = 0;
	while (cmd->names->proc[i] && i + 1 < cmd->names->index)
		waitpid(cmd->names->proc[i++], NULL, 0);
	waitpid(cmd->names->proc[i], &state, 0);
	return (state);
}

int main(int argc, char **argv, char **env)
{
    char	*cmd;
	char	*args[] = {"ls", "-a", "-l", NULL};
	
	cmd = ft_strdup("/usr/bin/ls");
    ft_execution(cmd, argv, env);
    {
        
    }
}