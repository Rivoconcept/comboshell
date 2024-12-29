/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:20:34 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/29 14:41:29 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_cmd_fields(t_cmd *cmd) {
    if (cmd == NULL)
        return;
    if(cmd->cmd && ft_strcmp(cmd->cmd[0], "|") == 0)
    {
        free_array(cmd->cmd);
        cmd->cmd = NULL;
    }
    if (cmd->less) {
        free(cmd->less);
        cmd->less = NULL;
    }
    if (cmd->great) {
        free(cmd->great);
        cmd->great = NULL;
    }
    if (cmd->dgreat) {
        free(cmd->dgreat);
        cmd->dgreat = NULL;
    }

    cmd->here = 0;
    cmd->rank_here = 0;
    cmd->flag_less = 0;
    cmd->rank_less = 0;
    cmd->rank_great = 0;
    cmd->rank_dgreat = 0;
}

static void del_in(t_cmd *input, int here) {
    int i = 0;
    int j = 0;
    int in_rank = 0;

    while (input->cmd[i] != NULL) {
        if (ft_strcmp(input->cmd[i], "<<") == 0 && is_char_valid(input->cmd[i + 1])) {
            input->rank_here = in_rank++;
            input->here = here;
            free(input->cmd[i]);
            free(input->cmd[i + 1]);
            i++;
        } else if (ft_strcmp(input->cmd[i], "<") == 0 && input->cmd[i + 1]) {
            input->rank_less = in_rank++;
            if (input->less)
                free(input->less);
            input->less = ft_strdup(input->cmd[i + 1]);
            free(input->cmd[i + 1]);
            free(input->cmd[i]);
            i++;
        } else {
            input->cmd[j++] = input->cmd[i];
        }
        i++;
    }
    input->cmd[j] = NULL;
    if (j == 0) {
        free(input->cmd);
        input->cmd = NULL;
    }
}

static void del_out(t_cmd *out)
{
    int i = 0;
    int j = 0;
    int out_rank = 0;

    while (out->cmd[i] != NULL)
    {
        if ((ft_strcmp(out->cmd[i], ">") == 0  || ft_strcmp(out->cmd[i], ">>") == 0) && out->cmd[i + 1])
            handle_out_redirection(out, &out_rank, &i, out->cmd[i]);
        else
            out->cmd[j++] = out->cmd[i];
        i++;
    }
    out->cmd[j] = NULL;
    if (j == 0) {
        free(out->cmd);
        out->cmd = NULL;
    }
}

void handle_head_with_next(t_params *params, t_cmd *current, t_cmd *node_to_delete) {
    params->command = node_to_delete->next;
    params->command->next = NULL;
    free_cmd_fields(current);
    free(current);
    free_cmd_fields(node_to_delete);
    free(node_to_delete);
}

void handle_head_without_next(t_params *params, t_cmd *current, t_cmd *node_to_delete) {
    params->command = node_to_delete;
    params->command->next = NULL;
    free_cmd_fields(current);
    free(current);
}

void handle_middle_with_next(t_cmd *current, t_cmd *node_to_delete) {
    if (current->previous) {
        current->previous->next = node_to_delete->next;
    }
    if (node_to_delete->next) {
        node_to_delete->next->previous = current->previous;
    }
    free_cmd_fields(current);
    free(current);
    free_cmd_fields(node_to_delete);
    free(node_to_delete);
}

void handle_middle_without_next(t_cmd *current, t_cmd *node_to_delete, t_cmd *previous) {
    previous->next = NULL;
    free_cmd_fields(current);
    free(current);
    free_cmd_fields(node_to_delete);
    free(node_to_delete);
}

void handle_end_node(t_params *params, t_cmd *current, t_cmd *previous) {
    if (current == params->command) {
        free_cmd_fields(current);
        free(current);
        params->command = NULL;
    } else if (previous && ft_strcmp(previous->cmd[0], "|") == 0 && previous->previous) {
        t_cmd *node_to_delete = previous->previous;
        if (node_to_delete) {
            node_to_delete->next = NULL;
        }
        free_cmd_fields(current);
        free(current);
        free_cmd_fields(previous);
        free(previous);
    } else if (previous && ft_strcmp(previous->cmd[0], "|") == 0 && !previous->previous) {
        previous->next = NULL;
        free_cmd_fields(current);
        free(current);
    }
}

void handle_empty_command(t_params *params, t_cmd *current, t_cmd *next, t_cmd *previous) {
    t_cmd *node_to_delete;

    if (next && next->cmd && ft_strcmp(next->cmd[0], "|") == 0) {
        node_to_delete = next;
        if (current == params->command && node_to_delete->next) {
            handle_head_with_next(params, current, node_to_delete);
        } else if (current == params->command && !node_to_delete->next) {
            handle_head_without_next(params, current, node_to_delete);
        } else if (current != params->command && node_to_delete->next) {
            handle_middle_with_next(current, node_to_delete);
        } else if (current != params->command && !node_to_delete->next) {
            handle_middle_without_next(current, node_to_delete, previous);
        }
    } else if (!next) {
        handle_end_node(params, current, previous);
    }
}

void free_commands_and_nodes_if_empty(t_params *params) {
    if (params == NULL || params->command == NULL)
        return;

    t_cmd *current = params->command;
    t_cmd *next;
    t_cmd *previous;

    while (current) {
        next = current->next;
        previous = current->previous;

        if (current->cmd == NULL) {
            handle_empty_command(params, current, next, previous);
            current = params->command;
        } else {
            current = next;
        }
    }
}

void manage_red(t_params *params) {
    int rank_cmd = 0;
    t_cmd *current = params->command;

    while (current != NULL) {
        t_cmd *next = current->next;
        del_in(current, rank_cmd);
        rank_cmd++;
        current = next;
    }
    free_commands_and_nodes_if_empty(params);
    current = params->command;
    while (current != NULL) {
        t_cmd *next = current->next;
        del_out(current);
        current = next;
    }
    free_commands_and_nodes_if_empty(params);
}


void input_r(t_cmd *current, int num_cmd, t_params *params, int child) {
    int fd_in;
    char *file;

    if (current->here >= 0 || current->less) {
        if (current->less && (current->here < 0 || current->rank_here < current->rank_less)) {
            fd_in = open_input_file(current->less, params, O_RDONLY, child);
            if (fd_in >= 0)
            {
                dup2_stdin(fd_in, current->less);
                close(fd_in);
            }
        } else if (current->here >= 0) {
            file = prepare_temp_file(num_cmd);
            fd_in = open_input_here(file, params, O_RDONLY, child);
            if (fd_in >= 0)
            {
                dup2_stdin(fd_in, file);
                unlink(file);
                free(file);
                close(fd_in);
            }
        }
    }
}

void output(t_cmd *current, t_params *params) {
    int fd_out;

    if (current->great || current->dgreat) {
        if (current->great && (!current->dgreat || current->rank_dgreat < current->rank_great)) {
            fd_out = open_file(current->great, params, O_WRONLY | O_CREAT | O_TRUNC);
            dup2_stdout(fd_out, current->great);
            close(fd_out);

        } else if (current->dgreat) {
            fd_out = open_file(current->dgreat, params, O_WRONLY | O_CREAT | O_APPEND);
            dup2_stdout(fd_out, current->dgreat);
            close(fd_out);
        }
    }
}