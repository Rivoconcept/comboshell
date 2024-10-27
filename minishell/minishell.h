/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:59 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/27 16:28:44 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stddef.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


#include "./ljosia/ljosia.h"
// #include "./libft/libft.h"
#include "./RIVO/rivo.h"

#define MAX_CHILDREN 1024

typedef struct s_children {
    pid_t pids[MAX_CHILDREN];
    int count;
} t_children;

typedef struct s_context {
    int fd[2];
    int fd_close;
} s_context;

typedef enum e_tokentype {
    END_TOKEN = 0,
    CMD_TOKEN = 1,
	PIPE_TOKEN = 2,
    STR_TOKEN = 3,
    COL_TOKEN = 4,
    HERE_TOKEN = 5, // <<
    LESS_TOKEN = 6, // <
    GREAT_TOKEN = 7, // >
    DGREAT_TOKEN =8 // >>
} e_tokentype;

typedef struct s_element {
    e_tokentype type;
    char *value;
    struct s_element *next;
} s_element;

typedef struct s_slice {
    char *start;
    size_t length;
} s_slice;

typedef struct s_token {
    e_tokentype type;
    s_slice location;
} s_token;

typedef struct Node s_node;

typedef enum e_nodetype {
    ERROR_NODE = -1,
    CHAR_NODE = 0,
    PAIR_NODE = 1,
    STR_NODE = 2
} e_nodetype;

typedef struct s_pairvalue {
    s_node *left;
    s_node *right;
} s_pairvalue;

typedef union {
    s_pairvalue pair;
    char value;
    char *error;
    char *str;
} u_nodevalue;

struct Node {
    e_nodetype type;
    u_nodevalue data;
};

// clean_arg.c
char *join_argv(char **argv);

// exec.c
void exec(const s_node *node);
int exec_node(const s_node *node, s_context *ctx, t_children *children);
int exec_pipe(const s_node *node, s_context *ctx, t_children *children) ;
int exec_command(char **argv, s_context *ctx, t_children *children);

// ft_cmd.c
char	*check_shell(char *path);
char *is_valid_cmd(char *path, char *cmd);

// ft_multiline.c
char *multiline(char **input);

// ft_path.c
char	*get_path(char *envp[], char *rgx);

// guard.c
void* guard(void *ptr, char *file, int number);

// here_doc_utils.c
char **here_key(char *input);

// here_doc.c
void process_here(char **keys);

// list.c
s_element *add_element(s_element *list, char *value, e_tokentype type);
void print_elements(s_element *list);
void free_elements(s_element *list);
char **list_to_array(s_element *list);

// node.c 
s_node *strnode_new(char *c);
s_node *charnode_new(char c);
s_node *pairnode_new(s_node *left, s_node *right);
s_node *errornode_new(char *msg);
void *node_drop(s_node *node);

// parser.c
s_node *parse(char *itr, int *i);

// quote.c
int check_quote(char *str);
int dquote_length(char *str, int pos, char quote);

// real_path.c
int is_absolute_path(const char *path);
int is_executable_name(const char *path);
char* simplify_path(const char *path);

// scanner.c
int len_word(char *str, int *start);
s_token scanner_peek(char *itr, int *i);
int scanner_has_next(char *itr, int *i);
s_token scanner_next(char *itr, int *i);

// signal.c
void register_child(t_children *children, pid_t pid);
void terminate_children(t_children *children);
void sig_handler(int signal);
void signal_handlers(int sign);

// tokens.c
int has_next(const char *itr, int *i);
char peek(const char *itr, int *i);
char next(char *itr, int *i, int length);

// vector.c
char* extract_word(char *input, int *i);
char* extract_redirection(char *input, int *i);
s_element *parse_cmd(char *input);

#endif
