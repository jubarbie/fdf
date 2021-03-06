/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 10:47:22 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/07 17:11:03 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include "get_next_line.h"
#include "math.h"

void	check_good_file(char *file_name)
{
	int		fd;
	int		ret;
	char	buf[100];

	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit(EXIT_FAILURE);
	ret = read(fd, buf, 99);
	buf[ret] = '\0';
	if (ret == 0)
		exit(EXIT_FAILURE);
	while (ret >= 0)
		if (!(allowed_char(buf[ret--])))
			exit(EXIT_FAILURE);
	close(fd);
}

void	move_img(int keycode, t_param *param)
{
	if (keycode == 0)
		POSX -= 20;
	if (keycode == 2)
		POSX += 20;
	if (keycode == 13)
		POSY -= 20;
	if (keycode == 1)
		POSY += 20;
}

int		ft_key(int keycode, t_param *param)
{
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	if (keycode == 49)
		init_pos(param);
	if (keycode == 5)
		PERS -= (PERS > 1) ? 0.4 : 0;
	if (keycode == 17)
		PERS += (PERS < 4) ? 0.4 : 0;
	if (keycode == 125)
		ALT -= (ALT > -10) ? 1 : 0;
	if (keycode == 0 || keycode == 2 || keycode == 13 || keycode == 1)
		move_img(keycode, param);
	if (keycode == 126)
		ALT += (ALT < 10) ? 1 : 0;
	if (keycode == 78)
		ZOOM -= (ZOOM > 0.4) ? 0.2 : 0;
	if (keycode == 69)
		ZOOM += (ZOOM < 2.8) ? 0.2 : 0;
	return (0);
}

int		main(int ac, char **av)
{
	t_param	*param;

	if (ac != 2)
		ft_putendl("usage: ./fdf source_file");
	else
	{
		check_good_file(av[1]);
		param = init_param(1200, 800, av[1], av[1]);
		create_img(param);
		mlx_expose_hook(WIN, create_img, param);
		mlx_loop_hook(MLX, create_img, param);
		mlx_key_hook(WIN, ft_key, param);
		mlx_loop(MLX);
	}
	return (0);
}
