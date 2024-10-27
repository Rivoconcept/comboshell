/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:01:52 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/27 16:10:33 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void exec(const s_node *node) {
    t_children children = { .count = 0 };
    
    s_context ctx = {
        {STDIN_FILENO, STDOUT_FILENO},
        -1
    };
    
    int children_count = exec_node(node, &ctx, &children);
    
    int remaining = children_count;
    
    while (remaining > 0) {
        for (int i = 0; i < children_count; i++) {
            if (children.pids[i] == -1) 
                continue;
            
            int status;
            pid_t result = waitpid(children.pids[i], &status, 0);
            
            if (result > 0) {
                remaining--;
                children.pids[i] = -1;
            } 
            else if (result == -1) {
                if (errno == ECHILD) {
                    remaining--;
                    children.pids[i] = -1;
                } else {
                    terminate_children(&children);
                    return;
                }
            }
        }
    }
    terminate_children(&children);
}

int exec_node(const s_node *node, s_context *ctx, t_children *children) {
    char **argv;

    if (node->type == PAIR_NODE) {
        return exec_pipe(node, ctx, children);
    } else if (node->type == STR_NODE) {
        argv = list_to_array(parse_cmd(node->data.str));
        return exec_command(argv, ctx, children);
    }
    return 0;
}


int exec_pipe(const s_node *node, s_context *ctx, t_children *children) {
    int p[2];
    int children_count = 0;
    s_context lhs_ctx;
    s_context rhs_ctx;

    if (pipe(p) == -1) {
        perror("pipe");
        return 0;
    }

    const s_node *lhs = node->data.pair.left;
    lhs_ctx = *ctx;
    lhs_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    lhs_ctx.fd_close = p[STDIN_FILENO];
    children_count += exec_node(lhs, &lhs_ctx, children);

    const s_node *rhs = node->data.pair.right;
    rhs_ctx = *ctx;
    rhs_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
    rhs_ctx.fd_close = p[STDOUT_FILENO];
    children_count += exec_node(rhs, &rhs_ctx, children);

    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
    return children_count;
}

int exec_command(char **argv, s_context *ctx, t_children *children) {
    pid_t child_pid = fork();
    if (child_pid == 0) {
        dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
        dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
        if (ctx->fd_close >= 0)
            close(ctx->fd_close);
        execvp(argv[0], argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (child_pid > 0) {
        register_child(children, child_pid);
    }
    ft_free(argv, count_array(argv));
    return 1;
}