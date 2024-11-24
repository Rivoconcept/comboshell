/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:11:18 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/10 11:11:18 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void read_pids(int *child_pids, int *child_count) {
    int fd = open(PID_FILE, O_RDONLY);
    if (fd == -1) return;

    char buf[12];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[bytes_read] = '\0';
        child_pids[(*child_count)++] = ft_atoi(buf);
    }
    close(fd);
}

static void read_child_proc(int *child_pids, int child_count, int sig) {
    for (int i = 0; i < child_count; i++) {
        kill(child_pids[i], sig);
        waitpid(child_pids[i], NULL, 0);
    }
}

void catch_ctrl_c(int sig, siginfo_t *info, void *ucontext) {
    (void)info;
    (void)ucontext;
    if (sig != SIGINT) return;
    
    int child_pids[1024];
    int child_count = 0;
    read_pids(child_pids, &child_count);
    if (child_count > 0) {
        read_child_proc(child_pids, child_count, SIGTERM);
        unlink(PID_FILE);
        write(1, "\n", 1);
    } else {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void catch_sigquit(int sig, siginfo_t *info, void *ucontext) {
    (void)info;
    (void)ucontext;
    if (sig != SIGQUIT) return;

    int child_pids[1024];
    int child_count = 0;
    read_pids(child_pids, &child_count);
    if (child_count > 0) {
        read_child_proc(child_pids, child_count, SIGQUIT);
        unlink(PID_FILE);
        ft_putendl_fd("Quit (core dumped)", 2);
    }
}

void write_pid(pid_t pid) {
    char *c_pid;
    int fd;

    fd = open(PID_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd != -1) {
        c_pid = ft_itoa(pid);
        c_pid = ft_strjoin(c_pid, "\n");
        write(fd, c_pid, ft_strlen(c_pid));
        close(fd);
        free(c_pid);
    }
}