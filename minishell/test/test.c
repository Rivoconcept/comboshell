#include "test.h"

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Pour write() et sleep()

void handler(int num)
{
    (void)num;
    write(STDOUT_FILENO, "yes\n", strlen("yes\n"));
}

int main(void)
{
    struct sigaction sa;

    // Efface le masque de signaux
    sigemptyset(&sa.sa_mask);

    sa.sa_handler = handler;
    sa.sa_flags = 0;  // Pas de flags spécifiques

    // Attache le handler aux signaux SIGINT et SIGTERM
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);  // Correction du signal ici

    while (1)
    {
        sleep(1);
        printf("kill me\n");
    }

    return (0);
}
