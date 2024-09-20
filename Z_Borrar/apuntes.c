/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apuntes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:01:18 by user              #+#    #+#             */
/*   Updated: 2024/05/20 10:01:19 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ! Para empezar

// There is a github repository that obeys the order of proceedings pretty 
// nicely: https://github.com/Swoorup/mysh
// Please make sure to do a lexer -> parser -> expander -> executor to make 
// your life easier. Here is a solid start.
// Make sure that you understand the shell syntax.

// ! Explicación básica del funcionamiento de una shell:

// 1. Lectura de comandos: La shell lee los comandos ingresados por el usuario 
// desde la línea de comandos o desde un script.

// 2. Análisis y tokenización: Los comandos ingresados se analizan y se 
// descomponen en partes individuales llamadas "tokens". Por ejemplo, en el 
// comando ls -l /home, ls, -l, y /home son tokens.

// 3. Búsqueda del comando: La shell busca el comando ingresado en su lista de 
// rutas predefinidas (usualmente especificadas en la variable de entorno PATH).
// Si el comando es encontrado, se procede a su ejecución. De lo contrario, la 
// shell muestra un mensaje de error indicando que el comando no fue encontrado.

// 4. Creación de procesos: La shell crea un proceso hijo utilizando la llamada 
// al sistema fork(). El proceso hijo será responsable de ejecutar el comando 
// ingresado.

// 5. Sustitución de imágenes de proceso: El proceso hijo reemplaza su imagen de
// proceso con la del programa correspondiente al comando ingresado utilizando 
// la llamada al sistema exec() o una de sus variantes.

// 6. Ejecución del comando: El proceso hijo ejecuta el comando con los 
// argumentos proporcionados por el usuario.

// 7. Espera del proceso hijo: Si el comando genera un proceso hijo, la shell 
// puede esperar a que ese proceso termine utilizando la llamada al sistema 
// wait(), para que pueda mostrar el resultado al usuario o realizar otras 
// tareas dependiendo de la configuración o el diseño de la shell.

// 8. Ciclo de comando: Una vez que se completa la ejecución del comando, 
// la shell vuelve al estado de lectura de comandos, esperando el siguiente 
// comando del usuario.

// ! GNU Bash Manual
// https://www.gnu.org/savannah-checkouts/gnu/bash/manual/