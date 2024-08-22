/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/08/22 09:07:56 by descamil         ###   ########.fr       */
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
	pid_t	*proc; 					// Array de numeros de los procesos 

	int		fd; 					// Numero del fd del archivo abierto
	int		index; 					// iterador de la lista de pid_t, para el waitpid
	int		fd_tmp; 				// fd temporal para la modificacion del dup2
	int		fd_infile; 				// fd del infile
	int		fd_outfile; 			// fd del outfile

	int		fd_pipe[2]; 			// fd temporal para escritura y lectura

}			t_names;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			*cmd;
	char			**args;
	t_files			*files;
	t_type			*type;
	t_names			*names;
	int				args_amount; 
	int				error;
	int				exit;
}					t_cmd;

typedef struct s_mini
{
	int			fd_tmp;
	int			num_comm;
	int			fd_history;
	int			shell_level;
	char		*input;
	t_env		*env;
	t_cmd		*cmd;
	t_flags		*flags;
	t_token		*token;
}				t_mini;




// ft_execution.c
void	ft_comm(t_cmd *cmd, t_mini *mini);
void	ft_error(char *str, int i);

// ft_utils.c
void	ft_mini_header(void);
int		ft_strstr_len(char **str);
void	ft_strstr_printf(char **str, int color);
int		ft_strnstrstr(char **str, char *locate);
char	**ft_strstr_join(char **str, char **str1);

// ft_final_values.c
int		ft_type(char *argv);
int		ft_strlen_dup(char *argv);
void	ft_files(t_cmd *cmd, t_mini *mini, t_files *files);
char	**ft_strstr_dup(char **str);

// ft_initialize.c
t_mini	*ft_initialize(char **env);

// ft_signals.c
void	ft_signal_management(int n);

// ft_lexer.c
void	ft_recive_input(t_mini *mini);

// ft_parser.c
int		ft_strtok(t_mini *mini, t_cmd **cmd, char *input);

// ft_split_pipe.c
char	**ft_split_pipe(const char *s, char c);

// // ft_expander.c
// int		ft_var(char *input);
// int		ft_size(char **names);
// int		ft_size_int(int *test);
// int		ft_var_mod(char **env, char **names);
// int		ft_final_var(int *k, char *input, int i);
// char	**ft_names_var(char *input, int *k1, int **position);
// char	*ft_remove_var(char *dst, const char *src, int num, int i);
// int		ft_strnstr_mini(const char *s1, const char *s2, size_t len);
// char	*ft_remove_wrong_var(char *str, int *wrong_value, int wrong);

// ft_split_red.c
char	**ft_split_red(const char *s, int i);

// ft_expander.c
char	*ft_expander(char **env, char *str);
// char	*ft_change_name_var(char *line);
// char	*ft_change_var(t_cmd *cmd, char *line, char **var_reminder);
// char	*ft_craft_result(char *final_line, char *line, char *var, int c);
// char	*ft_change_dollar_x_var(t_cmd *cmd, char *command, char *var_reminder);

// ft_expander_utils.c
// char	*ft_add_var_value(char *str1);
// int		ft_var_strcmp(char *str1, char *str2);
// char	*ft_change_line_value(char *line, char *value);
// char	*ft_compare_var_name(t_cmd *cmd, char *line, char *name_var);
// char	*ft_strjoin_custom(char *str1, char *str2, size_t i, size_t c);

// ft_printf_cmd.c
void	print_cmd(t_cmd *cmd, t_mini *mini);

// ft_check_input.c
char	**ft_check_input(t_mini *mini, char *input);

// ft_redirects.c
int		ft_count_redirect(t_mini *mini, char *input);

// ft_check_quotes.c
int		ft_locate_next_quote(int i, char *input, char quote);
int		ft_check_quote_pairs(char *input, int *i, char quote);
int		ft_check_quote(char *input, int simp_quote, int doub_quote, t_mini *mini);

// ft_check_pipes.c
int		ft_count_pipes(char *input);
char	**ft_split_pipes(char *input);
char	**ft_fill_matrix_pipes(char *input, char **splited_pipes_matrix);

// ft_check_redir.c
int		ft_redir_type(char *splited_arg);
int		ft_check_redir_arg(char **splited_pipes_matrix, int i);

// ft_check_operators.c
int		ft_check_special_char(char c);
char	ft_type_of_operator_char(int n);
int		ft_is_not_mayor_n_minor_char(char c);
int		ft_search_next_char(char *str, char c, int j);

// ft_commands.c
int		ft_count_args(char *input);
char	*ft_get_command(char *input);
t_cmd	*ft_last_command(t_cmd **cmd);
t_cmd	*ft_add_command(char *input, int i);

// ft_commands-2.c
void	ft_plus_one(int value1, int value2);
int		*ft_sizes_input(char *input, int argc);
int		ft_position(char *input, int *size, int stop);
void	ft_get_args(char *input, int argc, char ***args);
char	*ft_inside_argv(char *input, int *size, int stop);
int		ft_size_argv(char *input, int stop, int size, int index);

// ft_commands-3.c
int		ft_nothing(char *input, int i);
int		ft_nothing_r(char *input, int i);
int		ft_find_char(char *input, int i);
int		ft_process_quotes(char *input, int *i, int *first);
void	ft_process_space(char *input, int i, int *first, int *stop);

// ft_check_dollar.c
int		ft_isdigit_n_special_char(int n);
int		ft_check_dollar_n_digits(char *command, int i);
char	*ft_remove_dollar_n_digits(char *command, int i, int j);

// ft_check_home_direc.c
char	*ft_replace_home(char *str);
char	*ft_replace_value_of_var(char *str);
int		ft_check_relative_home(char *command);
char	*ft_replace_value_bis(char *str, int i, int j);

// ft_error_management.c
void	ft_many_args_error(char **argv);
void	ft_put_error(char *bash, char *file, char *error_msg);
void	ft_exit_error(t_mini *mini, char *error_msg, int exit_status);

// ft_free.c
void	free_t_cmd(t_cmd **cmd);
void	free_t_mini(t_mini *mini);

void	ft_strstr_free(char **str);

// ft_split_red.c
int		is_redirection(char c, char c1);

#endif
