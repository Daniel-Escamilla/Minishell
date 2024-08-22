Funciones de pipex utiles -->

	· ft_first_command
	· ft_midd_command
	· ft_last_command

	Los tres necesitan unicamente la estructura t_names .

	Diferencias entre ellos
	
		· ft_first_command necesita,
			{
				names->input
				names->fd_infile
				names->fd_pipe[1]
				names->argv[2]
				names->fd_tmp --> names->fd_pipe[0]
			}
		· ft_midd_command necesita,
			{
				names->argv[names->comm_midd]
				names->fd_pipe[0]
				names->fd_pipe[1]
				names->proc[names->index]
				names->fd_pipe
				names->fd_tmp
				names->comm_midd++
				names->fd_tmp --> names->fd_pipe[0]
			}
		· ft_last_command necesita,
			{
				names->outfile
				fd (fd_outfile creado unicamente en la funcion)
				names->fd_pipe[1]
				names->argv[names->argc - 2]
			}
	Todos ellos hacen,
		{
			names->index++;
		}

	void	ft_execute_bonus(t_names *names, char *argv)

		names->entire_comm = ft_split_bonus(argv, ' '); # Hecho --> llamado, cmd->args.
		if (names->entire_comm == NULL)
			ft_error_bonus("Bad split", 1);
		names->route = ft_validate_comm_bonus(names, 1); # Hecho --> llamado, cmd->cmd.
		if (names->fd_infile == -1)
		{
			names->fd_infile = 0;
			if (names->route != NULL)
				ft_error_bonus("Failed open input", 1);
			else
				write (2, "Command not found\n", 19);
		}
		execve(names->route, names->entire_comm, names->envp); # Cambio de nombres a cmd->cmd, cmd->args, mini->env->env

	void	ft_multiple(t_names *names, char **argv, char **envp, int argc)
	
	ft_first_comm(names);
	while (--names->num_comm > 2)
		ft_midd_comm(names);
	ft_last_comm(names);

_______________________________________________________________________________________________________________________________________________________________________________
_______________________________________________________________________________________________________________________________________________________________________________
_______________________________________________________________________________________________________________________________________________________________________________


	void	ft_execute(t_mini *mini)

		# names->entire_comm = ft_split_bonus(argv, ' '); # Hecho --> llamado, cmd->args.
		# if (names->entire_comm == NULL)
			# ft_error_bonus("Bad split", 1);
		# names->route = ft_validate_comm_bonus(names, 1); # Hecho --> llamado, cmd->cmd.
		# execve(names->route, names->entire_comm, names->envp); # Cambio de nombres a cmd->cmd, cmd->args, mini->env->env
		execve(cmd->cmd, cmd->args, mini->env->env);

	
	void	ft_multiple(t_names *names, char **argv, char **envp, int argc)
	
		ft_first_comm(names);
		while (--names->num_comm > 2)
			ft_midd_comm(names);
		ft_last_comm(names);









void	ft_setvalues(t_mini *mini)
{
	# names->argc = argc;
	# names->argv = argv;
	# names->envp = envp;
	# names->path = ft_create_path_bonus(names);
	# names->output = names->argv[names->argc - 1];
	# names->comm_midd = 3;
	# names->input = names->argv[1];
	# names->num_comm = names->argc - 3 + 1;
	
	mini->names->index = 0;

	mini->names->fd = 0;

	mini->names->num_comm = ft_count_comm();

	mini->names->proc = malloc(mini->names->num_comm * sizeof(int));

	
}












void	ft_first_comm(t_mini *mini)
{
	if (pipe(mini->names->fd_pipe) == -1)
		ft_error_bonus("Pipe error", 1);
	mini->names->proc[mini->names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (names->proc[names->index] == 0)
	{
		close(names->fd_pipe[0]);
		names->fd_infile = open(names->input, O_RDONLY);
		dup2(names->fd_infile, STDIN_FILENO);
		dup2(names->fd_pipe[1], STDOUT_FILENO);
		close(names->fd_infile);
		close(names->fd_pipe[1]);
		ft_execute_bonus(names, names->argv[2]);
	}
	names->fd_tmp = names->fd_pipe[0];
	names->index++;
	close(names->fd_pipe[1]);
}









void	ft_midd_comm(t_names *names)
{
	if (pipe(names->fd_pipe) == -1)
		ft_error_bonus("Pipe Error", 1);
	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Failed in Fork()", 1);
	if (names->proc[names->index] == 0)
	{
		close(names->fd_pipe[0]);
		dup2(names->fd_tmp, STDIN_FILENO);
		dup2(names->fd_pipe[1], STDOUT_FILENO);
		close(names->fd_tmp);
		close(names->fd_pipe[1]);
		ft_execute_bonus(names, names->argv[names->comm_midd]);
	}
	names->fd_tmp = names->fd_pipe[0];
	names->index++;
	names->comm_midd++;
	close(names->fd_pipe[1]);
}















void	ft_last_comm(t_names *names)
{
	int		fd;

	names->proc[names->index] = fork();
	if (names->proc[names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (names->proc[names->index] == 0)
	{
		fd = open(names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			close(names->fd_tmp);
			ft_error_bonus("Error open input", 1);
		}
		dup2(names->fd_tmp, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(names->fd_tmp);
		close(fd);
		ft_execute_bonus(names, names->argv[names->argc - 2]);
	}
	names->index++;
}