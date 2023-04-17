/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:45:49 by luhego            #+#    #+#             */
/*   Updated: 2023/04/17 17:47:33 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_fd_size(int fd)
{
	int		count;
	char	*tmp;

	tmp = get_next_line(fd);
	count = 0;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		count++;
	}
	return (count);
}

void ft_exit(int exit_code, char *arg, char **tab)
{
	int i;

    if (exit_code == 1)
        ft_putstr_fd("Error\nWrong file_type.\n", 1);
    if (arg)
        perror(arg);
    if (tab)
    {
		i = 0;
        while (tab[i])
        {
            free(tab[i]);
            i++;
        }
        free(tab);
    }
    exit(0);
}

char	**ft_create_map(char **argv)
{
	int		fd;
	int		i;
	int		fd_size;
	size_t	file_type;
	char	**map;

	i = 0;
	file_type = ft_strlen(argv[1]) - 4;
	if (ft_strncmp(&argv[1][file_type], ".ber", 4) != 0)
		ft_exit(1, 0, 0);
	fd = open(argv[1], O_RDONLY);
	fd_size = ft_fd_size(fd);
	map = malloc(sizeof(char *) * (fd_size + 1));
	if (!map)
		ft_exit(1, "malloc", 0);
	close(fd);
	return (map);
}

int	main(int argc, char **argv)
{
	char	**map;
	int		i;
	int		fd;
	int		fd_size;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	fd_size = ft_fd_size(fd);
	map = ft_create_map(argv);
	i = 0;
	if (!ft_parsing() && !ft_layout())
	{
		while (i != fd_size)
		{
			map[i] = get_next_line(fd);
			ft_putstr_fd(map[i], 1);
			i++;
		}
	}
	ft_exit(0, 0, map);
	return (0);
	// Parsing
	// Layout
	// 
}
