/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:45:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/30 21:39:18 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define HISTORY_FILE ".old_history"
# define READLINE_IGN ".readline.ign"

extern pid_t		g_sig_num;

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
	char			**cmd;
	int				here;
	int				rank_here;
	int				flag_less;
	char			*less;
	int				rank_less;
	char			*great;
	int				rank_great;
	char			*dgreat;
	int				rank_dgreat;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}					t_cmd;

typedef struct s_params
{
	t_cmd			*command;
	t_env			*myenvp;
	int				fd_in;
	int				fd_out;
	t_export		*myexport;
	char			**envp;
	int				last_exit_code;
	pid_t			*pid_tab;
	int				prev_pipe_read;
	int				rank_cmd;
	char			*new_input;
	char			**parsed;
}					t_params;

typedef struct s_here_data
{
	int				j;
	int				quote;
}					t_here_data;

// l_handle_here.c
int					handle_here(char *delimiter, char **here_content,
						t_here_data *here_data, t_params *params);
// l_expand.c
char				*expand_variable_in_input(char *line, t_params *params);
// l_del_utils.c
void				handle_out_redirection(t_cmd *out, int *out_rank, int *i,
						const char *type);
void				del_here(t_cmd *input, int *in_rank, int here, int *i);
void				del_less(t_cmd *input, int *in_rank, int *i);
void				free_cmd_fields(t_cmd *cmd);

// l_ft_utils_5.c
void				reset_cmd_flags(t_cmd *cmd);

// l_ft_utils_6.c
// void process_command(t_params *params, char **parsed);

// l_inout_utils.c
int					open_file(char *filename, t_params *params, int flags);
void				dup2_stdout(int fd_out, char *filename);
int					open_input_file(char *filename, t_params *params, int flags,
						int child);
int					open_input_here(char *filename, t_params *params, int flags,
						int child);
void				dup2_stdin(int fd_in, char *filename);
char				*prepare_temp_file(int num_cmd);

// clean_arg.c
char				*join_argv(char **argv);

// ft_check.c
int					check_less(t_params *params);
int					check_infile(t_cmd *current, t_params *params);
int					manage_less(t_params *params);

// ft_strcat.c
char				*ft_strcat(char *dest, char *src);

// ft_strcmp.c
// int	ft_strcmp(const char *first, const char *second);

// ft_strcpy.c
char				*ft_strcpy(char *s1, char *s2);

// ft_strndup.c
char				*ft_strndup(const char *s, size_t size);

// ft_realloc.c
// void *ft_realloc(void *ptr, size_t new_size);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);

// ft_subfirst.c
char				*ft_subfirst(char *s, unsigned int start, size_t len);
char				*ft_substrj(char *s, unsigned int start, size_t len);

// here_doc_utils.c
// char **here_key(char *input);
// char **here_key(char **input);
int					is_char_valid(const char *input);
int					manage_here(t_params *params);

// here_doc.c
// void process_here(char **input, char **keys, int j);
int					process_here(char **keys, int j, t_params *params);

// redirection.c
// t_element *redirect_io(t_element **elements, t_redirections *redirs);
// t_redirection *add_red(e_tokentype type, char *value, int rank);
// void free_redirections(t_redirections *redirs);
void				manage_red(t_params *params);
void				input_r(t_cmd *current, int num_cmd, t_params *params,
						int child);
void				output(t_cmd *current, t_params *params);

/**********************GET_NEXT_LINE ****************************************************************/

size_t				check_new_line(char *buffer);
size_t				check_back_slash_n(const char *s, int c);
char				*putline(char *readed_line);
char				*putlast(char *readed_line);
char				*ftstrjoin(char *old_str, char *buffer, size_t size);
char				*read_line(int fd, int *check, char *buffer,
						char *readed_line);
char				*get_next_line(int fd);

/***********************FT_RIVO************************************************************** */
void				print_cmd(t_params *params);

// ft_r_check_behavior.c
int					check_error_newline(char *s);
int					pass_error_test_1(char *s);
int					pass_error_test_2(char *s);
int					check_general_errors(char *s, t_params *params);

// r_exec_1.c
int					ft_get_pid_nbr(t_params *params);
void				exec_builtins(t_params *params, t_cmd *current);
int					ft_check_continue(t_params *params, t_cmd **current);
void				check_fork_error(t_params *params, t_cmd *current, int tab,
						int fd[2]);
void				exec_child_builtins(t_params *params, t_cmd *current);

// r_exec_2.c
void				exec_child(t_params *params, t_cmd *current, int fd[2]);
void				exec_child_process(t_params *params, t_cmd *current,
						int tab, int fd[2]);
int					call_exec_builtins(t_params *params);
void				check_pipe_error(t_cmd *current, int fd[2],
						t_params *params);
void				ft_handle_child(t_params *params);

// r_exec_3.c
void				wait_pid(t_params *params, t_cmd *current, int status);
void				exec_cmd(t_params *params);

// r_format_argv_1.c
char				*put_other_val(char *str, int *index, t_params *params);
char				*check_val_env(char *str, int *index, char *env_value,
						t_params *params);
void				put_var_env(char *input, int *i, char **temp,
						t_params *params);
int					is_in_myenvp(char *temp, t_env *myenvp);

// r_format_argv_2.c
int					realloc_new_str(size_t *size, char **new_str);
void				copy_env(size_t i[2], char *arg, char **new_str,
						t_params *params);
char				*format_var_env(char *arg, t_params *params);
void				format_variable(char **argv, t_params *params);
void				format_all_variable(t_params *params);

// r_format_cmd_1.c
char				*check_access(char *command, char *path);
char				*put_path(char **dirs, char *command);
char				*check_cmd_standard(t_params *params, char *command);
void				format_cmd(t_params *params);
void				delete_null_in_argv(t_params *params);

// r_format_cmd_2.c
t_cmd				*create_new_list_cmd(char **argv);
t_cmd				*add_command(t_cmd *command, char **argv);
t_params			*create_list_params(char **envp);

// r_format_input_1.c
int					is_operator(char c);
int					put_new_size(char *input);
void				add_spaces(char *new_str, char *input, int *i, int *j);
void				check_left_quote(char *input, int *j, int *lquote);
void				check_right_quote(char *input, int *k, int *rquote);

// r_format_input_2.c
int					check_pipe_out_quote(char *input, int i, char c);
int					check_echo(char *s, int *i, char *new_str, int *j);
char				*format_input(char *input);

// r_format_quotes_1.c
int					echap_quote(char c, int *in_single_quote,
						int *in_double_quote);
char				*format_quotes(char *command);
int					var_in_apostrophe(char *input, int i);
void				copy_var_env(char *env, char *new_str, int *index);
void				del_quotes(char **argv);

// r_format_quotes_2.c
void				handle_quotes(char c, int *in_single_quote,
						int *in_double_quote);
int					in_apostrophe(char *str);
int					in_quote(char *str);

// r_format_quotes_3.c
int					pure_apostrophe(char *str);
int					pure_quote(char *str);
int					in_single_quote(char *str);
int					in_double_quote(char *str);
void				delete_quotes(t_params *params);

// r_ft_builtins.c
int					isbuiltins(char *command);
int					cmd_not_found(t_params *params);
int					run_builtins(char **cmd, t_params *params);

// r_ft_cd_1.c
char				*format_tilde(t_params *params, char **dirs, char *cwd);
char				*return_new_path(const char *arg, t_params *params);
void				handle_cd(int *i, char *arg, char *new_path,
						t_params *params);

// r_ft_cd_2.c
void				return_oldpwd(t_params *params);
void				return_pwd(t_params *params);
int					ft_cd(const char *arg, t_params *params);

// r_ft_cleaner.c
void				free_array(char **arr);
void				free_list_env(t_env *myenv);
void				free_list_export(t_export *myexp);
void				free_list_cmd(t_cmd *command);
void				cleanup_and_exit(t_params *params, int status);

// r_ft_echo.c
int					check_dash_n(char *str);
int					ft_print_echo(char *input);
int					run_echo(char **cmd, int flag[2]);
int					ft_echo(char **cmd);

// r_ft_env_1.c
t_env				*create_new_list_env(char *envp);
int					create_env(t_env **myenvp, char *envp);
char				*put_env_val(t_env *myenv, char *name);

// r_ft_env_2.c
void				init_var_env(t_env *myenv, char **envp);
int					count_list_env(t_params *params);
char				**put_envp(t_params *params);

// r_ft_env_3.c
void				del_env_element(t_env **myenv, const char *name);
char				*ft_getenv(t_params *params, char *name);
int					ft_env(t_params *params);

// r_ft_exit.c
int					is_numeric(const char *str);
long long int		ft_atoi_lld(const char *str);
unsigned long long	ft_atoi_ull(const char *str);
int					check_errors_exit(char **parsed, t_params *params);
int					ft_exit(char **parsed, t_params *params);

// r_ft_export_1.c
int					print_export(t_params *params);
int					check_error_var_temp(char *cmd);
int					check_var_temp(char **cmd);
void				clean_export(char *exist_value, char *enter_value,
						char *name);

// r_ft_export_2.c
int					check_error_export(char *cmd);
char				*put_name_export(char *str);
char				*put_value_export(char *str);
t_export			*create_new_list_export(char *arg);
int					create_export(t_export **myexport, char *envp);

// r_ft_export_3.c
int					find_export_name(t_export *myexport, char *name);
int					del_export_element(t_export **myexport, char *envp);
char				*put_export_str(t_export *myexport, char *name);
char				*put_export_value(t_export *myexport, char *name);

// r_ft_export_4.c
int					handle_export_1(char *arg, t_params *params);
int					handle_export_2(char *arg, t_params *params);
int					handle_export_3(char *arg, t_params *params);
int					handle_export_4(char *arg, t_params *params);
int					ft_export(char **cmd, t_params *params);

// r_ft_history.c
int					ignore_leaks_readline(void);
void				add_old_history(void);
void				push_history(const char *line);

// r_ft_parser.c
void				handle_quote(char c, int *squote, int *dquote);
int					word_len(char *str);
int					word_count(char *str);
char				*split_word(char *str, int index);
char				**parse_command(char const *input);

// r_ft_pwd.c
int					ft_pwd(t_params *params);

// r_ft_unset.c
int					ft_unset(char **cmd, t_params *params);

// r_ft_utils_1.c
int					ft_is_space(char c);
int					find_char(char *str, char c);
int					while_check_char(char c, char *input);
int					find_first_index(const char *big, const char *little);

// r_ft_utils_2.c
int					check_input(char *s, char *base);
int					check_str(const char *big, const char *little, char *check);
char				*format_str_without_quote(char *input);
void				close_pipe(int fd[2]);

// r_ft_utils_3.c
int					count_cmd(t_cmd *command);
int					ft_strcmp(const char *s1, const char *s2);
int					putchar_count(const char *src, char c);

// r_ft_utils_4.c
void	perror_msg(char *path, char *error);
int	check_errors_path(char *path, char *parent_path, struct stat *statbuf,
		char *last_slash);
int	check_path(const char *path, t_params *params);


// r_ft_utils_5.c
int					check_is_all_space(char *input);
char				*check_is_path(char *command, char *path);
char				*check_access_path(char **dirs, char *command);
int					is_command(t_params *params, char *command);
int					check_errors(t_params *params);

// r_init_cmd_1.c
int					put_size(char **argv, int i);
int					add_separator(int var[3], char ***temp, t_cmd *cmd,
						char **argv);
int					initialize_cmd(int var[3], char ***temp, t_cmd *cmd,
						char **argv);
void				check_end_cmd(int var[3], char ***temp, t_cmd **cmd,
						char **argv);

// r_init_cmd_2.c
void				clean_cmd(t_cmd **cmd, char ***temp);
t_cmd				*init_command(char **argv);
void				free_command(t_cmd *command);
t_cmd				*remove_element_cmd(t_cmd *head, t_cmd *to_remove);
int					delete_cmd_null(t_params *params);

// r_signal.c
void				sig_handler(int signal);
void				signal_handlers(int sign);

void				print_list(t_cmd *command);
void				print_argv(char **argv);
void				print_cmd(t_params *params);

#endif