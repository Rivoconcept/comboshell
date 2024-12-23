/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:45:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/22 20:45:43 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdint.h>
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
#include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <signal.h>
#include <errno.h>
# include "./libft/libft.h"

extern volatile sig_atomic_t g_sig_num;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_export
{
	char			*name;
	char			*value;
	struct s_export	*next;
}					t_export;

typedef struct s_cmd
{
    char            **cmd;
	int             here;
    int             rank_here;
    int             flag_less;
    char            *less;
    int             rank_less;
    char            *great;
    int             rank_great;
    char            *dgreat;
    int             rank_dgreat;
    struct s_cmd    *next;
    struct s_cmd    *previous;
}                   t_cmd;

typedef struct s_params
{
	t_cmd			*command;
	t_env			*myenvp;
	int             fd_in;
    int             fd_out;
	t_export		*myexport;
	char			**envp;
	int				last_exit_code;
}					t_params;

// l_handle_here.c
void handle_here(char *delimiter, char **here_content, int j, int quote, t_params *params);
//l_expand.c
char *expand_variable_in_input(char *line, t_params *params);
//l_del_utils.c
void handle_out_redirection(t_cmd *out, int *out_rank, int *i, const char *type);
void del_here(t_cmd *input, int *in_rank, int here, int *i);
void del_less(t_cmd *input, int *in_rank, int *i);

//l_ft_utils_5.c
void reset_cmd_flags(t_cmd *cmd);

//l_ft_utils_6.c
//void process_command(t_params *params, char **parsed);

//l_inout_utils.c
int open_file(char *filename, int flags);
void dup2_stdout(int fd_out, char *filename);
int open_input_file(char *filename, int flags);
void dup2_stdin(int fd_in, char *filename);
char *prepare_temp_file(int num_cmd);

// clean_arg.c
char *join_argv(char **argv);

// ft_check.c
int check_less(t_params *params);
int check_infile(t_cmd *current);
void manage_less(t_params *params);

// ft_strcat.c
char *ft_strcat(char *dest, char *src);

// ft_strcmp.c
//int	ft_strcmp(const char *first, const char *second);

// ft_strcpy.c 
char    *ft_strcpy(char *s1, char *s2);

// ft_strndup.c
char	*ft_strndup(const char *s, size_t size);

// ft_realloc.c
//void *ft_realloc(void *ptr, size_t new_size);
void *ft_realloc(void *ptr, size_t old_size, size_t new_size);

// ft_subfirst.c
char	*ft_subfirst(char *s, unsigned int start, size_t len);
char	*ft_substrj(char *s, unsigned int start, size_t len);

// here_doc_utils.c
//char **here_key(char *input);
//char **here_key(char **input);
void manage_here(t_params *params);

// here_doc.c
//void process_here(char **input, char **keys, int j);
void process_here(char **keys, int j, t_params *params);


// redirection.c
//t_element *redirect_io(t_element **elements, t_redirections *redirs);
//t_redirection *add_red(e_tokentype type, char *value, int rank);
//void free_redirections(t_redirections *redirs);
void manage_red(t_params *params);
void input_r(t_cmd *current, int num_cmd);
void output(t_cmd *current);


/***********************FT_RIVO************************************************************** */
void print_cmd(t_params *params);

int word_count(char *str);
void print_argv(char **argv);
char **parse_command(const char *input);
void free_array(char **arr);
void free_list_cmd(t_cmd *command);
int	ft_strcmp(const char *s1, const char *s2);

t_cmd *add_command(t_cmd *command, char **argv);
void exec_cmd(t_params *params);
//void run_examshell(char *input, t_cmd *cmd, char **envp);

char	*join_paths(const char *path1, const char *path2);
int	standard_path(char **dirs, int *i, char **temp_path, t_params *params);

void	del_quotes(char **argv);

// r_format_quotes.c
int echap_quote(char c, int *in_single_quote, int *in_double_quote);
char *format_quotes(char *command);
int var_in_apostrophe(char *input, int i);
void copy_var_env(char *env, char *new_str, int *index);
void	del_quotes(char **argv);


// r_ft_env.c
void del_env_element(t_env **myenv, const char *name);
char *ft_getenv(t_params *params, char *name);
int ft_env(t_params *params);

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
void free_list_export(t_export *myexp);
void free_list_cmd(t_cmd *command);
void cleanup_and_exit(t_params *params, int status);

// r_init_list_env_1.c
char *put_env_name(char *envp);
char *put_env_value(char *envp);
int create_env(t_env **myenvp, char *envp);
char *put_env_val(t_env *myenv, char *name);

// r_init_list_env_2.c
void init_var_env(t_env *myenv, char **envp);
int count_list_env(t_params *params);
char **put_envp(t_params *params);


// r_format_cmd.c
char *check_access(char *command, char *path);
char *put_path(char **dirs, char *command);
char *check_cmd_standard(t_params *params, char *command);
int    format_path(char **argv, t_params *params);
void    format_cmd(t_params *params);

// r_ft_utils_1.c
int find_char(char *str, char c);
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
long long int	ft_atoi_lld(const char *str, int *overflow);
int	isoperator(char *input);
int check_path(const char *path);
int check_errors(t_params *params);
void	exit_error(const char *error);
void	*safe_malloc(size_t bytes);

// r_ft_is_token.c
int check_variable(char *arg);
int token_type(char *arg);

// r_format_argv.c
char *put_other_val(char *str, int *index, t_params *params);
char *check_val_env(char *str, int *index, char *env_value, t_params *params);
void put_var_env(char *input, int *i, char **temp, t_params *params);
char *format_var_env(char *arg, t_params *params);
void format_variable(char **argv, t_params *params);

// r_ft_export_1.c
int print_export(t_params *params);
int check_error_var_temp(char *cmd);
int check_var_temp(char **cmd);
void    clean_export(char *exist_value, char *enter_value, char *name);

// r_ft_export_2.c
int check_error_export(char *cmd);
char	*put_name_export(char *str);
char	*put_value_export(char *str);
t_export	*create_new_list_export(char *arg);
int	create_export(t_export **myexport, char *envp);

// r_ft_export_3.c
int	find_export_name(t_export *myexport, char *name);
int del_export_element(t_export **myexport, char *envp);
char	*put_export_str(t_export *myexport, char *name);
char	*put_export_value(t_export *myexport, char *name);

// r_ft_export_4.c
int    handle_export_1(char *arg, t_params *params);
int    handle_export_2(char *arg, t_params *params);
int    handle_export_3(char *arg, t_params *params);
int    handle_export_4(char *arg, t_params *params);
int ft_export(char **cmd, t_params *params);

//r_ft_unset.c
int ft_unset(char **cmd, t_params *params);

// r_ft_pwd.c
int ft_pwd(void);

// r_ft_echo.c
int check_dash_n(char *str);
int	ft_print_echo(char *input);
//int run_echo(char **cmd, int flag[2], int fd);
int run_echo(char **cmd, int flag[2]);
int ft_echo(char **cmd);

// r_check_quotes.c
int pure_apostrophe(char *str);
int pure_quote(char *str);
int in_single_quote(char *str);
int in_double_quote(char *str);

// r_handle_quotes.c
void handle_quotes(char c, int *in_single_quote, int *in_double_quote);
int in_apostrophe(char *str);
int in_quote(char *str);

// r_format_input.c
//int	put_new_size(char *input, char *operators);
//void	add_spaces(char *new_str, char *input, char c, int var[3]);
//void add_spaces(char *new_str, char *input, int var[3], char c);
//char	*format_input(char *input, char *operators);
//char *format_operators(char *input);
char *format_input(char *input);

// r_ft_builtins.c
int run_builtins(char **cmd, t_params *params);
int cmd_not_found(t_params *params);

// r_check_behavior.c
int check_error_newline(char *s);
int check_behavior(char *s);

// r_signal.c
//void register_child(t_children *children, pid_t pid);
//void terminate_children(t_children *children);
void sig_handler(int signal);
void signal_handlers(int sign);

t_params *create_list_params(char **envp);
char	*put_export_value(t_export *myexport, char *name);
char	*put_export_str(t_export *myexport, char *name);
int check_error_export(char *cmd);

//r_ft_exit.c
void	ft_exit(char **parsed, t_params *params);
int check_input_is_all_space(char *input);
int pass_errors_test(char *input);
int	is_command(t_params *params, char *command);
#endif