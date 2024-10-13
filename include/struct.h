/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:45:49 by descamil          #+#    #+#             */
/*   Updated: 2024/10/13 18:22:53 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../minishell.h"

typedef struct s_files
{
	char		**f_order;
	char		**order;
	int			error;
}				t_files;

typedef struct s_red
{
	int			si_ri;
	int			si_le;
	int			do_ri;
	int			do_le;
	int			number;
	int			red_error;
	char		*error;
}				t_red;

typedef struct s_token
{
	char		*input;
	char		**tokens;
}				t_token;

typedef struct s_flags
{
	int			pipe;
	int			quote;
	int			dollar;
	int			expander;
	int			locate_red;
	t_red		*redirect;
}				t_flags;

typedef struct s_env
{
	int			env_amount;
	char		*path;
	char		**env;
}				t_env;

typedef struct s_type
{
	int			infile;
	int			outfile;
	int			here_doc;
	int			append;
	char		*in;
	char		*out;
}				t_type;

typedef struct s_names
{
	char	*join;
	int		fd_outfile;
	int		fd_infile;
	int		fd_tmp;
	int		fd;

}			t_names;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**tmp;
	char			**args;
	char			**quote_args;
	char			*cmd;
	t_type			*type;
	t_files			*files;
	t_names			*names;
	int				exit;
	int				size;
	int				error;
	int				built;
	int				args_amount;
}					t_cmd;

typedef struct s_mini
{
	int			error;
	int			index;
	int			fd_tmp;
	int			single;
	int			here_doc;
	int			num_comm;
	int			fd_pipe[2];
	int			fd_history;
	int			shell_level;
	char		*input;
	char		**join;
	pid_t		*proc;
	double		qpr_error;
	t_env		*env;
	t_cmd		*cmd;
	t_flags		*flags;
	t_token		*token;
}				t_mini;

#endif
