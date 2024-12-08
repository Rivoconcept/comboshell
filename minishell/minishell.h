/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:59 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/08 14:55:19 by rrakoton         ###   ########.fr       */
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
#define MAX_CHILDREN 1024

typedef struct s_children
{
    pid_t pids[MAX_CHILDREN];
    int count;
} t_children;

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_params
{
	t_cmd			*cmd;
	t_env			*myenvp;
	char			**envp;
	char			*var_temp;
	int				status;
}					t_params;

/******************************************** */


// clean_arg.c
char *join_argv(char **argv);

// exec_utils.c
void node_list(const t_node *node, t_element **elements);
void wait_for_children(int num_cmds);
void close_pipes(int **pipes, int num_pipes);
int **create_pipes(int num_pipes);

// exec.c
int exec(const t_node *node, char *input, t_params *params);
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


/***********************FT_RIVO************************************************************** */

// r_check_behavior.c
int check_error_newline(char *s);
int check_behavior(char *s);

// r_check_quotes.c
int pure_apostrophe(char *str);
int pure_quote(char *str);
int in_single_quote(char *str);
int in_double_quote(char *str);

// r_format_argv.c
char *put_other_val(char *str, int *index, t_params *params);
char *check_val_env(char *str, int *index, char *env_value, t_params *params);
void put_var_env(char *input, int *i, char **temp, t_params *params);
char *format_var_env(char *arg, t_params *params);
void format_variable(char **argv, t_params *params);

// r_format_cmd.c
char *check_access(char *full_path, char *command, char *path);
char *put_path(char **dirs, char *command);
char *check_cmd_standard(t_params *params, char *command);
char	**format_argv(char *input);
char	**put_argv(char *input, t_params *params);

// r_format_input.c
int	put_new_size(char *input, char *operators);
void	add_spaces(char *new_str, char *input, char c, int var[3]);
char	*format_input(char *input, char *operators);

// r_format_quotes.c
int echap_quote(char c, int *in_single_quote, int *in_double_quote);
char *format_quotes(char *command);
int var_in_apostrophe(char *input, int i);
void copy_var_env(char *env, char *new_str, int *index);
void	del_quotes(char **argv);

// r_ft_cd1.c
char	*get_home(t_params *params);
char	*return_pdir(const char *cwd);
char	*join_paths(const char *path1, const char *path2);
int	standard_path(char **dirs, int *i, char **temp_path, t_params *params);

// r_ft_cd2.c
char	*split_path(char **dirs, char *temp_path, t_params *params);
char	*format_tilde(t_params *params, char **dirs);
char	*return_new_path(const char *arg, t_params *params);
int	ft_cd(const char *arg, t_params *params);

// r_ft_cleaner.c
void free_list_env(t_env *myenv);
void free_list_cmd(t_cmd *command);
void cleanup_and_exit(t_params *params, char *input, int status);

// r_ft_echo.c
int check_dash_n(char *str);
int	ft_print_echo(char *input, int fd);
//int run_echo(char **cmd, int flag[2], int fd);
int run_echo(char **cmd, int flag[2]);
int ft_echo(char **cmd);

// r_ft_env.c
void del_env_element(t_env **myenv, const char *name);
char *ft_getenv(t_params *params, char *name);
void print_env(t_params *params);
void ft_env(t_params *params);

// r_ft_export.c
int check_error_var_temp(char *cmd);
int put_var_temp(char **cmd, t_params *params);
int ft_export(char **cmd, t_params *params);

// r_ft_is_token.c
int check_variable(char *arg);
int token_type(char *arg);

// r_ft_pwd.c
int ft_pwd(void);

// r_ft_utils_1.c
void print_prompt();
int ft_is_space(char c);
int while_check_char(char c, char *input);
int find_first_index(const char *big, const char *little);
void free_array(char **arr);

// r_ft_utils_2.c
int check_input(char *s, char *base);
int check_str(const char *big, const char *little, char *check);
char    *format_str_without_quote(char *input);
void close_pipe(int fd[2]);

// r_ft_utils_3.c
int	isbuiltins(char *command);
int count_cmd(t_params *params);
int	ft_strcmp(const char *s1, const char *s2);
int putchar_count(const char *src, char c);

// r_ft_utils_4.c
void init_var_env(t_env *myenv, char **envp);
int count_list_env(t_params *params);
char **put_envp(t_params *params);
void put_val_exit_status(t_params *params);

// r_handle_quotes.c
void handle_quotes(char c, int *in_single_quote, int *in_double_quote);
int in_apostrophe(char *str);
int in_quote(char *str);

// r_init_list_env.c
char *put_env_name(char *envp);
char *put_env_value(char *envp);
void create_env(t_env **myenvp, char *envp);
char *put_env_val(t_env *myenv, char *name);

// r_init_list_params.c
t_cmd *create_new_cmd(char *input, t_params *params);
t_cmd *create_list_cmd(char **split_cmd, t_params *params);
t_cmd *return_commands(char *input, t_params *params);
t_params *create_list_params(char **envp);

// r_parser.c
int put_word_len(char *str);
int ft_check_quote(char c, char *str, int *i);
int word_count(char *str);
char *split_word(char *str, int index);
char **parse_command(char const *input);

// r_signal.c
void register_child(t_children *children, pid_t pid);
void terminate_children(t_children *children);
void sig_handler(int signal);
void signal_handlers(int sign);

// r_ft_builtins.c
int cmd_not_found(t_params *params, char *input);
int run_builtins(char **cmd, t_params *params, char *input);

#endif
