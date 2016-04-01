/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:39:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/01 12:27:53 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "fdf.h"
#include "libft.h"

void	img_put_pixel(t_param *param, int x, int y, unsigned int color)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	b = ((color & 0xFF0000) >> 16);
	g = ((color & 0xFF00) >> 8);
	r = ((color & 0xFF));
	IMG_ADDR[y * SIZELINE + x * (BPP / 8)] = r;
	IMG_ADDR[y * SIZELINE + x * (BPP / 8) + 1] = g;
	IMG_ADDR[y * SIZELINE + x * (BPP / 8) + 2] = b;
}

t_pix	get_pix(t_param *param, int i, int j)
{
	t_pix	pix;
	int		z;

	z = ft_atoi(MAP[j][i]) * ALT;
	pix.x = (CT1 * (i * 10 * ZOOM) - CT2 * (j * 10 * ZOOM));
	pix.y = ((CT1 / PERS) * (i * 10 * ZOOM) + (CT2 / PERS) * (j * 10 * ZOOM) - (z * (ZOOM / 2)));
	if (z < 0)
		pix.color = mlx_get_color_value(MLX, 0x008A084B);
	else if (z)
		pix.color = mlx_get_color_value(MLX, 0x00FF00FF);
	else
		pix.color = mlx_get_color_value(MLX, 0x0000FF00);
	return (pix);
}

void	get_img_param(t_param *param)
{
	WIDTH = get_pix(param, MAP_X - 1, 0).x - get_pix(param, 0, MAP_Y - 1).x + 10;
	HEIGHT = (get_pix(param, MAP_X - 1, MAP_Y - 1).y - get_pix(param, 0, 0).y + 10) * 2;
	POSX = (WIN_X / 2) - (WIDTH / 2);
	POSY = (WIN_Y / 2) - (HEIGHT / 2);
	printf("WIDTH:%d\nHEIGHT:%d\n", WIDTH, HEIGHT);
}

int		create_img(t_param *param)
{
	int				i;
	int				j;
	unsigned int	color;

	j = -1;
	mlx_destroy_image(MLX, IMG);
	get_img_param(param);
	IMG = mlx_new_image(MLX, WIDTH, HEIGHT);
	IMG_ADDR = mlx_get_data_addr(IMG, &BPP, &SIZELINE, &ENDIAN);
	while (++j < MAP_Y)
	{
		i = -1;
		while (++i < MAP_X)
		{
			color = mlx_get_color_value(MLX, 0x00FF0000);
			if (j < (MAP_Y - 1))
				img_draw_line(param, get_pix(param, i, j),
													get_pix(param, i, j + 1));
			if (i < (MAP_X - 1))
				img_draw_line(param, get_pix(param, i, j),
													get_pix(param, i + 1, j));
		}
	}
	mlx_put_image_to_window(MLX, WIN, IMG, POSX, POSY);
	return (0);
}
