#include "minishell.h"

void print_elements(s_element *list)
{
    while (list) {
        printf("Type: %d\n", list->type);
        printf("Element: %s\n", list->value);
        list = list->next;
    }
}

void free_elements(s_element *list)
{
    while (list) {
        s_element *next = list->next;
        free(list->value);
        free(list);
        list = next;
    }
}

s_element *add_element(s_element *list, char *value, e_tokentype type)
{
    s_element *new_elem = (s_element *)malloc(sizeof(s_element));
    new_elem->value = ft_strdup(value);
    new_elem->type = type;
    new_elem->next = NULL;

    if (!list)
        return new_elem;
    s_element *temp = list;
    while (temp->next)
        temp = temp->next;
    if (temp->type == type && temp->type == HERE_TOKEN)
    {
        free(new_elem);
        free(temp->value);
        temp->value = ft_strdup(value);
    } else
        temp->next = new_elem;
    return list;
}

static int count_elements(s_element *list) {
    int count = 0;
    while (list) {
        count++;
        list = list->next;
    }
    return count;
}

static void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

char **list_to_array(s_element *list)
{
    int count;
    char **args;
    int i;

    i = 0;
    count = count_elements(list);
    args = (char **)malloc((count + 1) * sizeof(char *));
    if (!args)
        return NULL;
    while (list) {
        remove_newline(list->value);
        args[i] = ft_strdup(list->value);
        list = list->next;
        i++;
    }
    args[i] = NULL;
    free_elements(list);
    return args;
}