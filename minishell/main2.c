/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:46:29 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/15 11:26:39 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

// https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?pli=1&gid=0#gid=0

// https://www.youtube.com/watch?v=ubt-UjcQUYg;
// https://www.youtube.com/watch?v=SToUyjAsaFk
// https://www.youtube.com/watch?v=H61EC4CZnx8&t=729s

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void execute_command(char *cmd[], int input_fd, int output_fd) {
    if (input_fd != 0) {
        dup2(input_fd, STDIN_FILENO);  // Redirige l'entrée
        close(input_fd);
    }
    if (output_fd != 1) {
        dup2(output_fd, STDOUT_FILENO); // Redirige la sortie
        close(output_fd);
    }
    //  val = execve(argv[0], argv, envp);;  // Exécute la commande
    execvp(cmd[0], cmd);  // Exécute la commande
    perror("execvp failed");
    exit(1);
}

int main(int argc, char **argv) {
    int fd[2];  // Descripteurs pour le pipe
    int input_fd;  // Descripteur pour rediriger l'entrée depuis le fichier
    pid_t pid;

    // Ouvrir fichier.txt pour redirection d'entrée
    input_fd = open("fichier.txt", O_RDONLY);
    if (input_fd < 0) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Première commande : `cat < fichier.txt`
    pipe(fd);  // Crée un pipe pour la communication entre processus
    pid = fork();
    if (pid == 0) {
        // Enfant pour `cat`
        close(fd[0]);  // Ferme la lecture du pipe
        execute_command((char *[]){"cat", NULL}, input_fd, fd[1]);  // Redirection vers le pipe
    }
    close(fd[1]);  // Le parent ferme l'écriture du pipe

    // Deuxième commande : `grep "fille"`
    int fd2[2];
    pipe(fd2);
    pid = fork();
    if (pid == 0) {
        // Enfant pour `grep`
        close(fd2[0]);  // Ferme la lecture du second pipe
        execute_command((char *[]){"grep", "fille", NULL}, fd[0], fd2[1]);
    }
    close(fd[0]);  // Le parent ferme la lecture du premier pipe
    close(fd2[1]);  // Le parent ferme l'écriture du second pipe

    // Troisième commande : `wc -l`
    pid = fork();
    if (pid == 0) {
        // Enfant pour `wc -l`
        execute_command((char *[]){"wc", "-l", NULL}, fd2[0], STDOUT_FILENO);
    }
    close(fd2[0]);  // Le parent ferme la lecture du second pipe
    while (wait(NULL) > 0);

    return 0;
}
