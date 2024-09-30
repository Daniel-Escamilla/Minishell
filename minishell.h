/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/30 19:49:08 by user             ###   ########.fr       */
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

# include "include/struct.h"
# include "include/main.h"
# include "include/utils.h"
# include "include/files.h"
# include "include/parser.h"
# include "include/signals.h"
# include "include/builtins.h"
# include "include/executor.h"
# include "include/expander.h"
# include "include/redirects.h"

# include "libft/libft.h"

# include "get_next_line/get_next_line.h"

# define R 0
# define W 1

// valgrind --leak-check=full --show-leak-kinds=all
// --track-origins=yes --error-limit=no --tool=memcheck

extern int	g_exit_status;

#endif
