/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:19:58 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/01 11:40:57 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "mlx.h"
#include "get_next_line.h"
#include "fdf.h"

int			nb_coord(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (!(ft_isdigit(*str)) && *str != ' ')
			exit(EXIT_FAILURE);
		if (*str != ' '  && (*(str + 1) == '\0' || *(str + 1) == ' '))
			i++;
		str++;
	}
	return (i);
}

static char	***create_map(t_param *param, char *file_name)
{
	int		fd;
	char	*line;
	char	***tab;
	int		i;
	int		map_x;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit(EXIT_FAILURE);
	i = 0;
	while (get_next_line(fd, &line))
	{
		map_x = nb_coord(line);
		i++;
	}
	close(fd);
	if (!(tab = malloc(sizeof(char **) * i)) ||
				((fd = open(file_name, O_RDONLY)) == -1))
		exit(EXIT_FAILURE);
	i = 0;
	map_x = 100000000;
	while (get_next_line(fd, &line))
	{
		map_x = (nb_coord(line) < map_x) ? nb_coord(line) : map_x;
		tab[i++] = ft_strsplit(line, ' ');
	}
	close(fd);
	MAP_Y = i;
	MAP_X = map_x;
	return (tab);
}

t_param		*init_param(int size_x, int size_y, char *title, char *file_name)
{
	t_param	*param;

	if (!(param = (t_param *)malloc(sizeof(t_param))))
		exit(EXIT_FAILURE);
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, size_x, size_y, title);
	MAP = create_map(param, file_name);
	get_img_param(param);
	WIN_X = size_x;
	WIN_Y = size_y;
	POSX = (WIN_X / 2) - (WIDTH / 2);
	POSY = 0;
	BPP = 24;
	SIZELINE = WIDTH * (BPP / 8);
	ENDIAN = 0;
	CT1 = 1;
	CT2 = 1;
	ALT = 1;
	PERS = 2;
	ZOOM = 2;
	IMG = mlx_new_image(MLX, WIDTH, HEIGHT);
	IMG_ADDR = mlx_get_data_addr(IMG, &BPP, &SIZELINE, &ENDIAN);
	return (param);
}
