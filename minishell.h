/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/16 15:34:19 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Colors
# define RESET "\033[0m"

// Normal colors
# define RD_0 "\033[0;31m"    		// Rojo normal
# define RD_1 "\033[38;5;9m"  		// Rojo claro
# define RD_2 "\033[38;5;88m" 		// Rojo oscuro
# define GR_0 "\033[0;32m"    		// Verde normal
# define GR_1 "\033[38;5;10m" 		// Verde claro
# define GR_2 "\033[38;5;28m" 		// Verde oscuro
# define OR_0 "\033[38;5;214m" 		// Naranja normal
# define OR_1 "\033[38;5;208m" 		// Naranja claro
# define OR_2 "\033[38;5;220m" 		// Naranja oscuro
# define YE_0 "\033[38;5;229m" 		// Amarillo normal
# define YE_1 "\033[38;5;226m" 		// Amarillo claro
# define YE_2 "\033[38;5;227m"		// Amarillo oscuro
# define BL_0 "\033[0;34m"    		// Azul normal
# define BL_1 "\033[38;5;12m" 		// Azul claro
# define BL_2 "\033[38;5;19m" 		// Azul oscuro
# define PR_0 "\033[0;35m"    		// Púrpura normal
# define PR_1 "\033[38;5;13m" 		// Púrpura claro
# define PR_2 "\033[38;5;56m" 		// Púrpura oscuro
# define CY_0 "\033[0;36m"    		// Cian normal
# define CY_1 "\033[38;5;14m" 		// Cian claro
# define CY_2 "\033[38;5;30m" 		// Cian oscuro
# define WH_0 "\033[0;37m"    		// Blanco normal
# define WH_1 "\033[38;5;15m" 		// Blanco claro
# define WH_2 "\033[38;5;145m"		// Blanco oscuro

// Bold colors
# define B_RD_0 "\033[1;31m"    		// Rojo normal en negrita
# define B_RD_1 "\033[1;38;5;9m"  	// Rojo claro en negrita
# define B_RD_2 "\033[1;38;5;88m" 	// Rojo oscuro en negrita
# define B_GR_0 "\033[1;32m"   		// Verde normal en negrita
# define B_GR_1 "\033[1;38;5;10m" 	// Verde claro en negrita
# define B_GR_2 "\033[1;38;5;28m" 	// Verde oscuro en negrita
# define B_OR_0 "\033[1;38;5;214m" 	// Naranja normal en negrita
# define B_OR_1 "\033[1;38;5;208m" 	// Naranja claro en negrita
# define B_OR_2 "\033[1;38;5;220m" 	// Naranja oscuro en negrita
# define B_YE_0 "\033[1;38;5;226m" 	// Amarillo normal en negrita
# define B_YE_1 "\033[1;38;5;227m" 	// Amarillo claro en negrita
# define B_YE_2 "\033[1;38;5;229m" 	// Amarillo oscuro en negrita
# define B_BL_0 "\033[1;34m"    		// Azul normal en negrita
# define B_BL_1 "\033[1;38;5;12m" 	// Azul claro en negrita
# define B_BL_2 "\033[1;38;5;19m" 	// Azul oscuro en negrita
# define B_PR_0 "\033[1;35m"    		// Púrpura normal en negrita
# define B_PR_1 "\033[1;38;5;13m" 	// Púrpura claro en negrita
# define B_PR_2 "\033[1;38;5;56m" 	// Púrpura oscuro en negrita
# define B_CY_0 "\033[1;36m"    		// Cian normal en negrita
# define B_CY_1 "\033[1;38;5;14m" 	// Cian claro en negrita
# define B_CY_2 "\033[1;38;5;30m" 	// Cian oscuro en negrita
# define B_WH_0 "\033[1;37m"    		// Blanco normal en negrita
# define B_WH_1 "\033[1;38;5;15m" 	// Blanco claro en negrita
# define B_WH_2 "\033[1;38;5;145m" 	// Blanco oscuro en negrita

// Librerias
# include "get_next_line.h"

# include "libft/libft.h"

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/param.h>
# include <readline/readline.h>
# include <readline/history.h>
# define R 0
# define W 1

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-limit=no --tool=memcheck

extern int	g_exit_status;

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
	char			*cmd;
	t_files			*files;
	t_type			*type;
	t_names			*names;
	int				args_amount; 
	int				error;
	int				built;
	int				exit;
	int				size;
}					t_cmd;

typedef struct s_mini
{
	pid_t		*proc;
	
	int			error;
	int			index;
	int			fd_tmp;
	int			here_doc;
	int			num_comm;
	int			fd_pipe[2];
	int			fd_history;
	int			shell_level;
	char		*input;
	char		**join;
	t_env		*env;
	t_cmd		*cmd;
	t_flags		*flags;
	t_token		*token;
}				t_mini;

// ft_builtin.c
int		ft_exec_built(t_cmd *cmd);
char	*ft_builtins(t_cmd *cmd, char *comm);

// ft_change_env.c
void	ft_change_env(char ***env, char *variable, char *content);

// ft_change_var.c
char	*ft_change_var(char *div, char **env);

// ft_check_dollar.c
int		ft_isdigit_n_special_char(int i);
int		ft_check_dollar_n_digits(char *command, int i);
char	*ft_remove_dollar_n_digits(char *command, int i, int j);

// ft_check_home_dir.c
char	*ft_replace_home(char *str);
char	*ft_replace_value_of_var(char *str);
int		ft_check_relative_home(char *command);
char	*ft_replace_value_of_var_bis(char *str, int i, int j);

// ft_check_input.c
char	**ft_check_input(t_mini *mini, char *input);

// ft_check_operators.c
int		ft_is_not_mayor_n_minor_char(char c);

// ft_check_pipes.c
int		ft_count_pipes(char *input, int amount, int character);
int		ft_pipe_error(char *input, int i);

// // ft_check_quotes.c
int		ft_locate_next_quote(int i, char *input, char quote);
int		ft_check_quote_pairs(char *input, int *i, char quote);
int		ft_check_quote(char *input, int simp_quote, int doub_quote, t_mini *mini);

// ft_check_redir.c
int		ft_redir_type(char *splited_arg);
int		ft_check_redir_arg(char **splited_pipes_matrix, int i);

// ft_comm_exec.c
void	ft_comm(t_cmd *cmd, t_mini *mini);
void	ft_comm_part1(t_cmd *cmd, t_mini *mini);
void	ft_comm_part2(t_cmd *cmd, t_mini *mini);
void	ft_comm_part3(t_cmd *cmd, t_mini *mini);

// ft_commands-2.c
void	ft_plus_one(int value1, int value2);
int		*ft_sizes_input(char *input, int argc);
void	ft_free(char **argv, int *size, char ***args);
int		ft_position(char *input, int *size, int stop);
void	ft_get_args(char *input, int argc, char ***args);
char	*ft_inside_argv(char *input, int *size, int stop);
int		ft_size_argv(char *input, int stop, int size, int index);

// ft_commands-3.c
int		ft_nothing(char *input, int i);
int		ft_nothing_r(char *input, int i);
int		ft_find_char(char *input, int i);
int		ft_process_quotes(char *input, int *i, int *first);

// ft_commands.c
int		is_red(char *argv);
int		ft_count_args(char *input);
t_cmd	*ft_last_command(t_cmd **cmd);
t_cmd	*ft_add_command(char *input, int i);

// ft_do_expander.c
void	ft_do_expander(t_mini *mini, t_cmd *cmd);
char	**ft_str_expander(t_mini *mini, char **args);

// ft_error_management.c
void	ft_many_args_error(int argc, char **argv);
// void	ft_put_error(char *bash, char *file, char *error_msg);
// void	ft_exit_error(t_mini *mini, char *error_msg, int exit_status);

// ft_exec_cmd.c
void	ft_comm(t_cmd *cmd, t_mini *mini);
char	*ft_validate_comm(char *cmd, char **path, int j);
char	*ft_route_cmd(t_mini *mini, t_cmd *current, char *tmp);

// ft_expand_div.c
char	*expand_div(int *iter, char *str, char **env);

// ft_expander.c
char	*ft_expander(char **env, char *str);

// ft_expander_utils1.c
int		ft_size_var(char *str);
char	*ft_dolar_to_iqual(char *div);
char	*ft_join(char **div, char *tmp);

// ft_expander_utils2.c
char	*ft_free_null(char *str);
void	ft_ex_free(char **div, char *tmp);
char	*ft_no_more_dolar(char *div, char *str);

// ft_expander_utils.c

// ft_fds_infile.c
int		ft_more(t_cmd *cmd, int i, int type);
int		ft_pick_infile(t_cmd *cmd, t_mini *mini);

// ft_fds_outfile.c
int		ft_pick_outfile(t_cmd *cmd, t_mini *mini);
int		ft_handle_trunc(t_cmd *cmd, t_mini *mini, int i);
int		ft_handle_append(t_cmd *cmd, t_mini *mini, int i);

// ft_files.c
int		ft_pos_files(t_cmd *cmd, int i);
int		ft_mem_files(t_mini *mini, t_cmd *cmd);
void	ft_files(t_cmd *cmd, t_mini *mini, t_files *files);

// ft_files_utils.c
void	ft_select_files(t_cmd *cmd, int i);
void	ft_move_files(t_cmd *cmd, t_mini *mini);
void	ft_remove_files(t_cmd *cmd, t_mini *mini);
void	ft_process_file(char *str, int *count, int *check, char **dest);
void	process_lines(t_cmd **cmd, t_mini *mini, char **lines, int i);

// ft_final_values.c
int		ft_type(char *argv);
int		ft_num_files(t_cmd *cmd);
int		ft_check_dups(t_cmd *cmd);
void	ft_type_file(t_cmd *cmd, int type);
char	**ft_order(t_cmd *cmd, t_mini *mini);

// ft_free.c
void	free_t_cmd(t_cmd **cmd);
void	free_t_env(t_env **env);
void	free_t_mini(t_mini *mini);
void	ft_free_sim(void *ptr, char *str, char *str1);
void	ft_free_dou(void *ptr, char **str, char **str1);

// ft_here_doc.c
int		ft_here_doc(t_cmd *cmd, int last, int i);

// ft_initialize.c
t_mini	*ft_initialize(char **env);
t_mini	*ft_free_resources(t_mini *mini, int stage);

// ft_lexer.c
int		ft_find_exit(char *input);
void	ft_recive_input(t_mini *mini);
int		ft_check_void_input(char *input);
char	*ft_free_input(t_mini *mini, char *input);
void	ft_free_per_comm(t_mini *mini, char *input);

// ft_main.c
int		main(int argc, char **argv, char **env);

// ft_manage_fd.c
void	ft_close_fd(t_mini *mini, int who);
void	ft_open_fd(t_cmd *cmd, t_mini *mini);
int		ft_choose_infile(t_cmd *cmd, t_mini *mini);
int		ft_choose_outfile(t_cmd *cmd, t_mini *mini);

// ft_new_args.c
void	ft_new_args(t_cmd *current, int *i);
void	ft_free_fcheck_args(char **args1, char **args2);
char	**ft_change_args(char **args, int pos, int i, int j);

// ft_parser.c
int		ft_sizes(t_cmd *current);
void	ft_start_val(t_cmd *cmd);
int		ft_wait_bonus(t_mini *mini);
char	**ft_create_path(char **env);

// ft_printf_cmd.c
void	print_cmd(t_cmd *cmd);

// ft_redirects.c
int		ft_red(char *input);
void	ft_start_red(t_mini *mini);
void	ft_red_error(t_mini *mini, char *input);
int		ft_count_redirect(t_mini *mini, char *input, int i);
int		ft_redirect_size(t_mini *mini, char *input, int *i);

// ft_redirects_utils.c
int		ft_red_count(t_mini *mini);
void	ft_one(t_mini *mini, char *input);
void	ft_two(t_mini *mini, char *input);
void	ft_three(t_mini *mini, char *input);
void	ft_four_plus(t_mini *mini, char *input);

// ft_save_path.c
char	*ft_execute(char **env);
char	**ft_save_path(char **env);
char	*ft_father(int *fd, char **args);
void	ft_pid_0(int *fd, char *path, char **args, char **env);

// ft_select_cmd.c
void	ft_select_cmd(t_cmd *current, t_mini *mini, int j);

// ft_signals.c
void	ft_signal_management(int i);
void	ft_signal_handler(int signal);
void	ft_child_signal_handler(int signal);

// ft_split_pipe.c
void	*free_memory_pipe(int a, char **arr);
char	**ft_split_pipe(const char *s, char c);
int		ft_strlen_pipe(const char *s, int i, char c);
char	*ft_strlcpy_pipe(char *s, char c, int *new_start, int size);

// ft_split_red.c
int		is_redirection(char c, char c1);
char	**ft_split_red(const char *input, int i);
char	*extract_token(const char *input, int *i);
char	*extract_redirection(const char *input, int *i);
void	add_token(char **tokens, int *token_count, const char *token);

// ft_strtok.c
int		ft_minus_one(t_mini *mini);
int		ft_do_comm(t_cmd *cmd, t_mini *mini);
int		ft_strtok(t_mini *mini, t_cmd **cmd, char *input);
int		ft_order_all(t_mini *mini, t_cmd **cmd, char **lines, char *input);

// ft_str_utils2.c
int		ft_strlen_dup(char *argv);
void	ft_strstr_unlink(t_mini *mini);
char	**ft_sindub_join(char **str, char *str1);
char	*ft_strchr_mod(char *str, int value, int stop);

// ft_str_utils.c
int		ft_strstr_len(char **str);
void	ft_strstr_free(char **str);
char	**ft_strstr_dup(char **str);
int		ft_strnstrstr(char **str, char *locate);
char	**ft_strstr_join(char **str, char **str1);

// ft_tript.c
char	**ft_tript(char *str, int size, int start);

// ft_utils.c
int		ft_history(void);
void	ft_mini_header(void);
void	ft_error(char *str, int i);
void	ft_strstr_printf(char **str);

#endif
