#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork(); // Crear el primer proceso hijo (Hijo1)

    if (pid1 == 0)
    { 
        // Código del primer proceso hijo (Hijo1)
        printf("Soy el primer proceso hijo con PID %d\n", getpid());

        pid_t pid2 = fork(); // Crear el segundo proceso hijo (Hijo2)

        if (pid2 == 0)
        {
            // Código del segundo proceso hijo (Hijo2)
            printf("Soy el segundo proceso hijo con PID %d\n", getpid());
        }
        else
        {
            // Hijo1 espera a que Hijo2 termine
            wait(NULL);
            printf("Hijo2 ha terminado, ahora Hijo1 (PID %d) puede terminar\n", getpid());
        }
    }
    else
    {
        // Código del proceso padre (Padre1)
        wait(NULL); // Padre1 espera a que Hijo1 termine
        printf("Hijo1 ha terminado, ahora Padre1 (PID %d) puede terminar\n", getpid());
    }

    return 0;
}
