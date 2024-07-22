/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:34:11 by smarin-a          #+#    #+#             */
/*   Updated: 2024/06/26 15:14:51 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_signal_handler(int signal)
{
	//Manejo de SIGINT (Ctrl+C)
	if (signal == SIGINT)
	{
		//Reemplazar la línea actual en el buffer de entrada con una cadena
		//vacía, lo que básicamente borra la línea de entrada actual.
		rl_replace_line("", 0);
		write(1, "\n", 1);
		//Notifica a la biblioteca readline que se ha cambiado de línea.
		rl_on_new_line();
		//Vuelve a mostrar el prompt y cualquier contenido en la línea de 
		//entrada.
		rl_redisplay();
		g_exit_status = 1;
	}
	//Manejo de SIGQUIT (Ctrl+)
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	ft_child_signal_handler(int signal)
{
	//Si la señal recibida es SIGINT, la función establece la variable global 
	//exit_status en 130. Esto es una convención común en sistemas Unix, donde
	//un proceso que termina debido a una señal SIGINT devuelve un código de 
	//salida de 128 más el número de la señal, que en el caso de SIGINT es 2. 
	//Por lo tanto, 128 + 2 = 130.
	if (signal == SIGINT)
		g_exit_status = 130;
	//Si la señal recibida es SIGQUIT, la función imprime el mensaje "Quit: 3\n"
	//en la salida estándar utilizando la función write(1, "Quit: 3\n", 10);. 
	//Esto es una convención común en sistemas Unix, donde un proceso que
	//termina debido a una señal SIGQUIT imprime un mensaje en la salida 
	//estándar. En este caso, el mensaje "Quit: 3\n" indica que la señal SIGQUIT
	//fue recibida. Luego, la función establece la variable global exit_status
	//en 131, que es 128 más el número de la señal SIGQUIT, que es 3.
	//Por lo tanto, 128 + 3 = 131.
	else if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 9);
		g_exit_status = 131;
	}
	return ;
}

void	ft_signal_management(int i)
{
	struct sigaction	sig_act;

	sigemptyset(&sig_act.sa_mask);
	/*
	struct sigaction 
	{
    void (*sa_handler)(int);    					// Puntero a la función de manejo de señales
    sigset_t sa_mask;          						// Conjunto de señales bloqueadas durante la ejecución del manejador
    int sa_flags;               					// Opciones de comportamiento
    void (*sa_sigaction)(int, siginfo_t *, void *); // Puntero a una función de manejo de señales alternativa
	};
	*/
	if (i)
		sig_act.sa_handler = &ft_signal_handler;
	else
		sig_act.sa_handler = &ft_child_signal_handler;
	//Esta bandera indica que las llamadas al sistema interrumpidas por una 
	//señal serán reiniciadas automáticamente después de que se maneje la señal.
	sig_act.sa_flags = SA_RESTART;
	/*
	Se llama a la función sigaction tres veces para establecer los manejadores
	de señales para SIGINT, SIGQUIT y SIGTERM utilizando la configuración 
	especificada en sa.
	En cada llamada, se pasa el número de la señal correspondiente 
	(SIGINT, SIGQUIT o SIGTERM), un puntero a la estructura sa que contiene la
	configuración del manejador de señales, y NULL como tercer argumento.
	El tercer argumento es NULL porque no estamos interesados en almacenar la
	configuración anterior del manejador de señales.
	*/
	sigaction(SIGINT, &sig_act, NULL);
	sigaction(SIGQUIT, &sig_act, NULL);
	// sigaction(SIGTERM, &sig_act, NULL);
}
