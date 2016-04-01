/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 10:47:22 by jubarbie          #+#    #+#             */
/*   Updated: 2016/04/01 12:12:28 by jubarbie         ###   ########.fr       */
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

int	ft_key(int keycode, t_param *param)
{
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	if (keycode == 49)
	{
		ALT = 1;
		POSX = 100;
		POSY = 100;
		PERS = 2;
		ZOOM = 2;
	}
	if (keycode == 5)
	{
		POSY -= (PERS > 2) ? exp(0.5) : 0;
		PERS -= (PERS > 2) ? exp(-2) : 0;
	}
	if (keycode == 17)
	{
		POSY += (PERS < 5) ? exp(0.5) : 0;
		PERS += (PERS < 5) ? exp(-2) : 0;	
	}
	if (keycode == 125)
		ALT -= (ALT > -10) ? 1 : 0;
	if (keycode == 0)
		POSX -= 20;
	if (keycode == 2)
		POSX += 20;
	if (keycode == 13)
		POSY -= 20;
	if (keycode == 1)
		POSY += 20;
	if (keycode == 126)
		ALT += (ALT < 10) ? 1 : 0;
	if (keycode == 78)
		ZOOM -= (ZOOM > 0.4) ? 0.2 : 0;
	if (keycode == 69)
		ZOOM += (ZOOM < 2.8) ? 0.2 : 0;
	//printf("%d\n", keycode);
	return (0);
}

int	main(int ac, char **av)
{
	t_param	*param;

	if (ac != 2)
		ft_putendl("usage: ./fdf source_file");
	else
	{
		param = init_param(1200, 800, "FDF", av[1]);
		//printf("WIDTH:%d\nHEIGHT:%d\n", WIDTH, HEIGHT);
		create_img(param);
		//printf("MAP_X: %d\nMAP_Y: %d\nALT: %d\nPERS: %f\n", MAP_X, MAP_Y, ALT, PERS);	
		mlx_expose_hook(WIN, create_img, param);
		mlx_loop_hook(MLX, create_img, param);
		mlx_key_hook(WIN, ft_key, param);
		mlx_loop(MLX);
	}
	return (0);
}
