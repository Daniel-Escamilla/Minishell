#------------------------------------------------------------------------------#
#******************************************************************************#
#********************************* C MAKEFILE *********************************#
#******************************************************************************#
#------------------------------------------------------------------------------#
# Antes de completar el Makefile, puedes ejecutar el siguiente comando para
# inicializar el proyecto:
# make init
# Este comando creará un archivo .gitignore con las extensiones mas comunes que
# se suelen ignorar en los proyectos de C para 42 y si lo deseas, te mostrará
# los comandos que puedes usar en este Makefile.
# ¡¡¡Recuerda que puedes añadir tus propias reglas al Makefile!!!
# ¡¡¡Buena suerte con tu proyecto!!!
#------------------------------------------------------------------------------#

# Nombre del ejecutable a crear (sin espacios)
NAME = minishell

#------------------------------------------------------------------------------#

# Compilador a utilizar (gcc, clang, etc)
CC = gcc
# Flags de compilacion (agregar los que se necesiten) -O2 para pruebas extra
CFLAGS = -g3 -Wall -Wextra -Werror #-Wpedantic -Wshadow -Wformat -Wnull-dereference -Wconversion -Wstrict-overflow -Wsign-conversion -Wimplicit-fallthrough=5 -Wdouble-promotion -Wvla -Wformat-security -Wcast-align=strict -Wredundant-decls -Wlogical-op -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Winit-self -Wuninitialized -Wbad-function-cast -Wmissing-field-initializers


# Incluir archivos de dependencia
-include $(OBJS:.o=.d)

#------------------------------------------------------------------------------#

# Archivos fuente (agregar los que se necesiten, separar por carpetas)
BUILTINS_SRCS =	src/builtins/ft_cd.c \
				src/builtins/ft_env.c \
				src/builtins/ft_pwd.c \
				src/builtins/ft_echo.c \
				src/builtins/ft_exit.c \
				src/builtins/ft_unset.c \
				src/builtins/ft_export.c \
				src/builtins/ft_builtin.c \
				src/builtins/ft_change_env.c \

EXECUTOR_SRCS = src/executor/ft_commands.c \
				src/executor/ft_exec_cmd.c \
				src/executor/ft_here_doc.c \
				src/executor/ft_new_args.c \
				src/executor/ft_manage_fd.c \
				src/executor/ft_save_path.c \
				src/executor/ft_comm_exec.c \
				src/executor/ft_fds_infile.c \
				src/executor/ft_select_cmd.c \
				src/executor/ft_fds_outfile.c \
				src/executor/ft_commands_utils.c \
				src/executor/ft_get_args_utils.c \

EXPANDER_SRCS =	src/expander/ft_tript.c \
				src/expander/ft_expander.c \
				src/expander/ft_change_var.c \
				src/expander/ft_expand_div.c \
				src/expander/ft_do_expander.c \
				src/expander/ft_expander_utils1.c \
				src/expander/ft_expander_utils2.c \

FILES_SRCS =	src/files/ft_files.c \
				src/files/ft_files_utils.c \
				src/files/ft_final_values.c \

MAIN_SRCS = 	src/main/ft_main.c \
				src/main/ft_initialize.c \
				src/main/ft_error_management.c \

PARSER_SRCS =	src/parser/ft_lexer.c \
				src/parser/ft_parser.c \
				src/parser/ft_strtok.c \
				src/parser/ft_split_pipe.c \
				src/parser/ft_check_input.c \
				src/parser/ft_quit_quotes.c \
				src/parser/ft_check_pipes.c \
				src/parser/ft_check_quotes.c \
				src/parser/ft_check_operators.c \

REDIRECT_SRCS =	src/redirects/ft_split_red.c \
				src/redirects/ft_redirects.c \
				src/redirects/ft_redirects_utils.c \

SIGNALS_SRCS =	src/signals/ft_signals.c \

UTILS_SRCS =	src/utils/ft_free.c \
				src/utils/ft_utils.c \
				src/utils/ft_utils2.c \
				src/utils/ft_str_utils.c \
				src/utils/ft_str_utils2.c \
				src/utils/ft_printf_cmd.c \

GNL_SRCS = 		src/get_next_line/get_next_line.c \
		   		src/get_next_line/get_next_line_utils.c \

SRCS =			$(GNL_SRCS) \
				$(MAIN_SRCS) \
				$(UTILS_SRCS) \
				$(FILES_SRCS) \
				$(PARSER_SRCS) \
				$(SIGNALS_SRCS) \
				$(BUILTINS_SRCS) \
				$(EXPANDER_SRCS) \
				$(EXECUTOR_SRCS) \
				$(REDIRECT_SRCS) \

#------------------------------------------------------------------------------#

# Archivos objeto (no tocar)
OBJS = $(SRCS:.c=.o)
# Directorio de los archivos objeto (no tocar)
OBJDIR = $(NAME)_objects
# Directorio de la libft. Si se usa, descomentar la linea
LIBFT_DIR = ./libft
# Libreria a utilizar. Si se usa, descomentar la linea
LIBFT = $(LIBFT_DIR)/libft.a

#------------------------------------------------------------------------------#

# Colores para el make.

# (Elige los colores que mas te gusten para el makefile. Elimina los que no
# necesites.)

# Recuerda siempre usar $(RESET) al final de tu mensaje para restablecer los
# colores a los valores predeterminados de la terminal.
RESET = \033[0m

# Regular
RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m

# Bold
BOLD_RED = \033[1;31m
BOLD_GREEN = \033[1;32m
BOLD_PURPLE = \033[1;35m

# More colors
B_C = \033[1;36m
YELLOW = \033[0;33m
BOLD_YELLOW = \033[1;33m
BLUE = \033[0;34m
BOLD_BLUE = \033[1;34m
MAGENTA = \033[0;35m
BOLD_MAGENTA = \033[1;35m
WHITE = \033[0;37m
BOLD_WHITE = \033[1;37m

#------------------------------------------------------------------------------#

LAST_MAKE_HAD_COMPILATION := 0

# Reglas del make (no tocar)

# La regla all compila el ejecutable
all: libft $(NAME)
	@if [ "$(LAST_MAKE_HAD_COMPILATION)" = "1" ]; then \
		clear; \
	else \
		echo "╔══════════╝ ╚══════════╝ ╚══════════╝ ╚══════════╝ ╚══════════╗"; \
		echo "║ $(B_C)(┌ಠ_ಠ)\t¡$(NAME) compilado con éxito!!\t(ಠ_ಠ┐)$(RESET) ║"; \
		echo "╚══════════════════════════════════════════════════════════════╝"; \
		sleep 1; \
		clear; \
	fi
	@$(eval LAST_MAKE_HAD_COMPILATION := 1)

# La regla $(NAME) compila el ejecutable con los archivos objeto creados
$(NAME): $(LIBFT) $(addprefix $(OBJDIR)/, $(OBJS))
	@echo "$(BOLD_GREEN)¡Objetos creados!\n$(RESET)"
	@echo "$(CYAN)Compilando $(NAME)...\n$(RESET)"
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OBJDIR)/, $(OBJS)) -lreadline $(LIBFT)

# La regla %.o compila los archivos objeto
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -c $< -o $@
	@$(eval LAST_MAKE_HAD_COMPILATION := 1)

# La regla $(OBJDIR) crea el directorio de los archivos objeto
$(OBJDIR):
	@echo "$(CYAN)Creando directorio de objetos...\n$(RESET)"
	@mkdir -p $(OBJDIR)/src/*
	@echo "$(BOLD_GREEN)¡Directorio de objetos creado!\n$(RESET)"
	@echo "$(CYAN)Creando objetos...\n$(RESET)"


# La regla libft compila la libft. Si se usa, descomentar las siguientes
# dos lineas
libft:
	@make -sC $(LIBFT_DIR) --no-print-directory

# La regla libft_clean elimina los archivos objeto de la libft. Si se usa,
# descomentar las siguientes dos lineas
libft_clean:
	@make -sC $(LIBFT_DIR) clean

# La regla libft_clean elimina los archivos objeto de la libft y el ejecutable.
# Si se usa, descomentar las siguientes dos lineas
libft_fclean:
	@make -sC $(LIBFT_DIR) fclean

# La regla clean elimina todos los archivos objeto y su directorio. Si se usa la
# libft, descomentar la linea libft_clean
clean: libft_clean
	@echo "$(RED)Eliminando archivos objeto...\n$(RESET)"
	@rm -rf $(addprefix $(OBJDIR)/, $(OBJS))
	@echo "$(BOLD_RED)¡Todos los archivos objeto han sido eliminados!\n$(RESET)"
	@echo "$(RED)Eliminando directorio de objetos...\n$(RESET)"
	@rm -rf $(OBJDIR)
	@echo "$(BOLD_RED)¡Directorio de objetos eliminado!\n$(RESET)"
	@clear

# La regla fclean elimina todos los archivos objeto y el ejecutable. Si se usa
# la libft, descomentar la linea libft_fclean
fclean: clean libft_fclean
	@echo "$(RED)Eliminando ejecutable...\n$(RESET)"
	@rm -rf $(NAME)
	@echo "$(BOLD_RED)¡El ejecutable ha sido eliminado!\n$(RESET)"
	@sleep 1
	@clear

# La regla re elimina todo y compila nuevamente
re: fclean all

# La regla init inicializa el proyecto
init:
	@bash -c 'read -p "Quieres ver los comandos de los que dispone este Makefile? [y/n]: " answer; \
	if [ "$$answer" = "y" ]; then \
		make --no-print-directory help; \
		read -p "Para continuar, presiona enter..."; \
	else \
		echo "Puedes ver los comandos con '\''make help'\'' en cualquier momento"; \
	fi'

# La regla test compila y ejecuta el programa con los argumentos que le pases
test: re
	@read -p "¿Cuántos argumentos quieres introducir? " num_args; \
	for ((i=1; i<=num_args; i++)); do \
		read -p "Introduce el argumento $$i: " arg; \
		args+=" $$arg"; \
	done; \
	./$(NAME)$$args

# Versión
VERSION = 1.10
version:
	@echo "Version: $(VERSION)"

# La regla git agrega, hace commit y hace push
git: fclean
	git add .
	git status
	@read -p "Quieres continuar? [y/n]: " answer; \
	if [ "$$answer" = "y" ]; then \
		read -p "Mensaje para el commit: " message; \
		git commit -m "$$message"; \
		git push; \
		clear; \
		echo "╔══════════════════════════════════════════════════════╗"; \
		echo "║ $(BOLD_GREEN)(┌ಠ_ಠ)\t ¡¡¡Git push realizado!!! \t(ಠ_ಠ┐)$(RESET) ║"; \
		echo "╚══════════════════════════════════════════════════════╝"; \
		sleep 0.5; \
		clear; \
	else \
		clear; \
		echo "╔════════════════════════════════════════════════════════╗"; \
		echo "║ $(BOLD_RED)(҂◕︵◕)\t¡¡¡Git push no realizado!!!\t (҂◕︵◕)$(RESET) ║"; \
		echo "╚════════════════════════════════════════════════════════╝"; \
		sleep 0.5; \
		clear; \
	fi

# La regla norm comprueba la norminette en las SRCS y en el .h
norm:
	@norminette $(SRCS) minishell.h | grep -v Norme -B1 || true

# La regla help muestra las reglas del make
help:
	@echo "\n"
	@echo ""
	@echo "$(BOLD_PURPLE)Reglas incluidas en el Makefile:$(RESET)"
	@echo ""
	@echo "  $(CYAN)all$(RESET)	-> Compila el ejecutable"
	@echo "  $(CYAN)clean$(RESET)	-> Elimina los archivos objeto"
	@echo "  $(CYAN)fclean$(RESET)-> Elimina los archivos objeto y el ejecutable"
	@echo "  $(CYAN)re$(RESET)	-> Elimina todo y compila nuevamente"
	@echo "  $(CYAN)init$(RESET)	-> Inicializa el proyecto"
	@echo "  $(CYAN)test$(RESET)	-> Compila y ejecuta el promgrama con los argumentos que le pases"
	@echo "  $(CYAN)git$(RESET)	-> Agrega, hace commit y hace push"
	@echo "  $(CYAN)norm$(RESET)	-> Ejecuta Norminette"
	@echo "  $(CYAN)help$(RESET)	-> Muestra las reglas del make"
	@echo ""

# La regla .PHONY indica que no hay un archivo llamado all, clean, fclean, 
# git, re, norm, help o libft
.PHONY: all clean fclean git re libft norm help
#------------------------------------------------------------------------------#