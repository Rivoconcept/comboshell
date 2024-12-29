#include "minishell.h"

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		printf("%s\n", argv[i]);
		// ft_putstr_fd(argv[i], 2);
		// ft_putstr_fd("\n", 2);
		i++;
	}
}
void	print_cmd(t_params *params)
{
	t_cmd	*current;

	current = params->command;
	while (current != NULL)
	{
		print_argv(current->cmd);
		current = current->next;
	}
	printf("*********************************************\n");
}
void	print_list(t_cmd *command)
{
	int	i;
	int	list_num;

	list_num = 1;
	while (command)
	{
		printf("Liste%d: ", list_num++);
		i = 0;
		while (command->cmd[i])
		{
			printf("%s ", command->cmd[i]);
			i++;
		}
		printf("\n");
		command = command->next;
	}
}