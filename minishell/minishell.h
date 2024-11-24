/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:59 by rrakoton          #+#    #+#             */
/*   Updated: 2024/11/24 13:15:04 by rrakoton         ###   ########.fr       */
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
//# include "./utils/utils.h"

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
} t_redirection;

typedef struct s_redirections {
    t_redirection *less;
    t_redirection *great;
    t_redirection *dgreat;
    t_redirection *here;
} t_redirections;

typedef struct s_element {
    e_tokentype type;
    char *value;
    struct s_element *next;
} t_element;

typedef struct s_slice {
    char *start;
    size_t length;
} t_slice;

typedef struct s_token {
    e_tokentype type;
    t_slice location;
} t_token;

typedef struct Node t_node;

typedef enum e_nodetype {
    ERROR_NODE = -1,
    CHAR_NODE = 0,
    PAIR_NODE = 1,
    STR_NODE = 2
} e_nodetype;

typedef struct s_pairvalue {
    t_node *left;
    t_node *right;
} t_pairvalue;

typedef union {
    t_pairvalue pair;
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
void node_list(const t_node *node, t_element **elements);
void wait_for_children(int num_cmds);
void close_pipes(int **pipes, int num_pipes);
int **create_pipes(int num_pipes);

// exec.c
int exec(const t_node *node);
// free.c
int count_array (char **argv);
void	*ft_free(char **ar, int index);

// ft_check.c
int	check_infile_err(char *infile, char *shell);
int	check_infile(char *infile);
int	check_outfile(char *outfile, char *shell);

// ft_cmd.c
char	*check_shell(char *path);
char *is_valid_cmd(char *path, char *cmd);

// ft_multiline.c
char *multiline(char **input);

// ft_strcat.c
char *ft_strcat(char *dest, char *src);

// ft_strcmp.c
int	ft_strcmp(const char *first, const char *second);

// ft_strcpy.c 
char    *ft_strcpy(char *s1, char *s2);

// ft_strndup.c
char	*ft_strndup(const char *s, size_t size);

// ft_realloc.c
void *ft_realloc(void *ptr, size_t new_size);

// ft_subfirst.c
char	*ft_subfirst(char *s, unsigned int start, size_t len);
char	*ft_substrj(char *s, unsigned int start, size_t len);

// ft_path.c
char	*get_path(char *envp[], char *rgx);

// guard.c
void* guard(void *ptr, char *file, int number);

// here_doc_utils.c
char **here_key(char *input);

// here_doc.c
void process_here(char **keys);

// list.c
t_element *add_element(t_element *list, char *value, e_tokentype type);
void print_elements(t_element *list);
void free_elements(t_element *list);
char **list_to_array(t_element *list);
int count_elements(t_element *list);

// node.c 
t_node *strnode_new(char *c);
t_node *charnode_new(char c);
t_node *pairnode_new(t_node *left, t_node *right);
t_node *errornode_new(char *msg);
void *node_drop(t_node *node);

// parser.c
t_node *parse(char *itr, int *i);

// quote.c
int check_quote(char *str);
int dquote_length(char *str, int pos, char quote);

// real_path.c
int is_absolute_path(const char *path);
int is_executable_name(const char *path);
char* simplify_path(const char *path);

// redirection_utils.c
void free_redirection(t_redirection *redir);
void handle_redirection(t_redirection **redir, e_tokentype type, char *value);
void remove_current_element(t_element **elements, t_element **prev, t_element **current);

// redirection.c
t_element *redirect_io(t_element **elements, t_redirections *redirs);
t_redirection *add_red(e_tokentype type, char *value);
void free_redirections(t_redirections *redirs);

// scanner.c
int len_word(char *str, int *start);
t_token scanner_peek(char *itr, int *i);
int scanner_has_next(char *itr, int *i);
t_token scanner_next(char *itr, int *i);

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
t_element *parse_cmd(char *input);

//format_argv.c
void format_variable(char **argv, t_params *params);

//format_cmd.c
char	**put_argv(char **argv, char *input, t_params *params);


#endif
