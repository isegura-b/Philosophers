#incude "../inc/philo.h"

void    ft_error(char *error_str, void set_free)
{
    printf("Error : %s\n", error_str);
    if (set_free)
        free(set_free);
    exit(EXIT_FAILURE);
}