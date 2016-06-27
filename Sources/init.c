/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:19:58 by jubarbie          #+#    #+#             */
/*   Updated: 2016/06/27 09:45:00 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		init_pos(t_param *param)
{
	ALT = 1;
	GAPX = 0;
	GAPY = 0;
	PERS = 2;
	ZOOM = 2;
}

int			allowed_char(char c)
{
	if (ft_isdigit(c) || c == '-' || c == ',' || c >= 'A' ||
			c <= 'F' || c == 'x' || c == ' ')
		return (1);
	return (0);
}

int			nb_coord(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (!(allowed_char(*str)))
			exit(EXIT_FAILURE);
		if (*str != ' ' && (*(str + 1) == '\0' || *(str + 1) == ' '))
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
	int		stop;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit(EXIT_FAILURE);
	MAP_Y = 0;
	while ((stop = get_next_line(fd, &line)) > 0)
			MAP_Y++;
	if (stop == -1 || MAP_Y == 0)
		exit(EXIT_FAILURE);
	close(fd);
	if (!(tab = malloc(sizeof(char **) * MAP_Y)) ||
				((fd = open(file_name, O_RDONLY)) == -1))
		exit(EXIT_FAILURE);
	MAP_Y = 0;
	MAP_X = 100000000;
	while ((stop = get_next_line(fd, &line)) > 0)
	{
		MAP_X = (nb_coord(line) < MAP_X) ? nb_coord(line) : MAP_X;
		tab[MAP_Y++] = ft_strsplit(line, ' ');
	}
	if (MAP_X < 1)
		exit(EXIT_FAILURE);
	close(fd);
	return (tab);
}

t_param		*init_param(int size_x, int size_y, char *title, char *file_name)
{
	t_param	*param;

	if (!(param = (t_param *)malloc(sizeof(t_param))))
		exit(EXIT_FAILURE);
	MAP = create_map(param, file_name);
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, size_x, size_y, title);
	WIN_X = size_x;
	WIN_Y = size_y;
	BPP = 24;
	SIZELINE = WIN_X * (BPP / 8);
	ENDIAN = 0;
	CT1 = 1;
	CT2 = 1;
	init_pos(param);
	IMG = mlx_new_image(MLX, WIN_X, WIN_Y);
	IMG_ADDR = mlx_get_data_addr(IMG, &BPP, &SIZELINE, &ENDIAN);
	return (param);
}
