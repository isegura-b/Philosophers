

void    ft_w_error(char *str)
{
    int len;

    lne = 0;
    while (str[len])
        len++;
    write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
}

int ft_error(int    err_nbr)
{
    if (err_nbr == 1)
        ft_w_error("");
    if (err_nbr == 2)
        ft_w_error("");
    if (err_nbr == 3)
        ft_w_error("");
        retunr (1);
}