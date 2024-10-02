/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:48:48 by descamil          #+#    #+#             */
/*   Updated: 2024/10/02 12:53:51 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INLCUDE_H
# define INCLUDE_H

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

# include "struct.h"
# include "main.h"
# include "utils.h"
# include "files.h"
# include "colors.h"
# include "parser.h"
# include "signals.h"
# include "builtins.h"
# include "executor.h"
# include "expander.h"
# include "redirects.h"

# include "../libft/libft.h"

# include "../get_next_line/get_next_line.h"


#endif