/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:59 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/27 18:51:07 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stddef.h>
# include <limits.h>
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

# include "./libft/libft.h"
# include "./utils/utils.h"

#define PID_FILE "/tmp/child_pids.txt"

typedef struct {
    pid_t *child_pids;
    int child_count;
} s_state;

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

typedef struct s_redirection {
    e_tokentype type;
    char *value;
} s_redirection;

typedef struct s_redirections {
    s_redirection *less;
    s_redirection *great;
    s_redirection *dgreat;
    s_redirection *here;
} s_redirections;

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

/********************************************** */
typedef struct s_params
{
	int				status;
	// struct s_params	*next;
}               t_params;

/******************************************** */

// clean_arg.c
char *join_argv(char **argv);

// exec_utils.c
void node_list(const s_node *node, s_element **elements);
void wait_for_children(int num_cmds);
void close_pipes(int **pipes, int num_pipes);
int **create_pipes(int num_pipes);

// exec.c
int exec(const s_node *node);

// ft_check.c
int	check_infile_err(char *infile, char *shell);
int	check_infile(char *infile);
int	check_outfile(char *outfile, char *shell);

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
int count_elements(s_element *list);

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

// redirection_utils.c
void free_redirection(s_redirection *redir);
void handle_redirection(s_redirection **redir, e_tokentype type, char *value);
void remove_current_element(s_element **elements, s_element **prev, s_element **current);

// redirection.c
s_element *redirect_io(s_element **elements, s_redirections *redirs);
s_redirection *add_red(e_tokentype type, char *value);
void free_redirections(s_redirections *redirs);

// scanner.c
int len_word(char *str, int *start);
s_token scanner_peek(char *itr, int *i);
int scanner_has_next(char *itr, int *i);
s_token scanner_next(char *itr, int *i);

// signal.c
void catch_ctrl_c(int sig, siginfo_t *info, void *ucontext);
void catch_sigquit(int sig, siginfo_t *info, void *ucontext);
void write_pid(pid_t pid);


// tokens.c
int has_next(const char *itr, int *i);
char peek(const char *itr, int *i);
char next(char *itr, int *i, int length);

// vector.c
char* extract_word(char *input, int *i);
char* extract_redirection(char *input, int *i);
s_element *parse_cmd(char *input);

//format_argv.c
void format_variable(char **argv, t_params *params);

//format_cmd.c
char	**put_argv(char **argv, char *input, t_params *params);

#endif
