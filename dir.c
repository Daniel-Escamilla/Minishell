/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:00:33 by user              #+#    #+#             */
/*   Updated: 2024/09/04 10:57:27 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Verificar que se haya pasado una ruta como argumento
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <ruta>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *ruta = argv[1];

    // Intentar cambiar al directorio especificado
    if (chdir(ruta) == 0) {
        printf("Cambio al directorio %s exitoso.\n", ruta);
    } else {
        // Si ocurre un error, se muestra un mensaje con el error
        fprintf(stderr, "mini: cd: %s: %s\n", ruta, strerror(errno));
        // perror("mini: cd: a");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

