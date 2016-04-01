/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:20:39 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/01 12:24:22 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "fdf.h"
#include "libft.h"

static void	line_case1(t_param *param, t_pix p1, t_pix p2, int pos_x)
{
	int				x;
	unsigned int	color1;
	unsigned int	color2;
	unsigned int	color;
	int				diff;

	x = p1.x;
	color1 = p1.color;
	color2 = p2.color;
	diff = p2.x - p1.x;
	color = color1;
	while (x <= p2.x)
	{
		color += (abs((int)color2 - (int)color1) / diff);
		img_put_pixel(param, x - pos_x, p1.y + ((p2.y - p1.y) * (x - p1.x)) /
														(p2.x - p1.x), color);
		x++;
	}
}

static void	line_case2(t_param *param, t_pix p1, t_pix p2, int pos_x)
{
	int				x;
	unsigned int	color1;
	unsigned int	color2;
	unsigned int	color;
	int				diff;

	x = p1.x;
	color1 = p1.color;
	color2 = p2.color;
	diff = p1.x - p2.x;
	color = color1;
	while (x > p2.x)
	{
		color += (abs((int)color2 - (int)color1) / diff);
		img_put_pixel(param, x - pos_x, p1.y + ((p2.y - p1.y) * (x - p1.x)) /
														(p2.x - p1.x), color);
		x--;
	}
}

static void	line_case3(t_param *param, t_pix p1, t_pix p2, int pos_x)
{
	int				y;
	unsigned int	color1;
	unsigned int	color2;
	unsigned int	color;
	int				diff;

	y = p1.y;
	color1 = p1.color;
	color2 = p2.color;
	diff = p1.y - p2.y;
	color = color1;
	while (y > p2.y)
	{
		color += (abs((int)color2 - (int)color1) / diff);
		img_put_pixel(param, p1.x + ((p2.x - p1.x) * (y - p1.y)) /
											(p2.y - p1.y) - pos_x, y, color);
		y--;
	}
}

static void	line_case4(t_param *param, t_pix p1, t_pix p2, int pos_x)
{
	int				y;
	unsigned int	color1;
	unsigned int	color2;
	unsigned int	color;
	int				diff;

	y = p1.y;
	color1 = p1.color;
	color2 = p2.color;
	diff = p2.y - p1.y;
	color = color1;
	while (y <= p2.y)
	{
		color += (abs((int)color2 - (int)color1) / diff);
		img_put_pixel(param, p1.x + ((p2.x - p1.x) * (y - p1.y)) /
											(p2.y - p1.y) - pos_x, y, color);
		y++;
	}
}

void		img_draw_line(t_param *param, t_pix p1, t_pix p2)
{
	int	pos_x;

	pos_x = get_pix(param, 0, MAP_Y - 1).x - get_pix(param, 0, 0).x - 5;
	if (p1.x <= p2.x && (p2.x - p1.x) >= abs(p2.y - p1.y))
		line_case1(param, p1, p2, pos_x);
	else if (p1.x > p2.x && (p1.x - p2.x) >= abs(p2.y - p1.y))
		line_case2(param, p1, p2, pos_x);
	else if (p1.y > p2.y && (p1.y - p2.y) >= abs(p2.x - p1.x))
		line_case3(param, p1, p2, pos_x);
	else
		line_case4(param, p1, p2, pos_x);
}
