/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 10:48:32 by jubarbie          #+#    #+#             */
/*   Updated: 2016/06/27 09:35:41 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include </System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "math.h"

# define MLX param->mlx
# define WIN param->win
# define POSX param->pos_x
# define POSY param->pos_y
# define GAPX param->gap_x
# define GAPY param->gap_y
# define GX param->gx
# define GY param->gy
# define WIN_X param->win_x
# define WIN_Y param->win_y
# define WIDTH param->width
# define HEIGHT param->height
# define CT1 param->ct1
# define CT2 param->ct2
# define ALT param->alt
# define MAP param->map
# define MAP_X param->map_x
# define MAP_Y param->map_y
# define BPP param->bpp
# define SIZELINE param->sizeline
# define ENDIAN param->endian
# define IMG param->img
# define IMG_ADDR param->img_addr
# define PERS param->pers
# define ZOOM param->zoom
# define BIMG param->bimg

typedef struct	s_param
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*bimg;
	int		win_x;
	int		win_y;
	int		pos_x;
	int		pos_y;
	int		gap_x;
	int		gap_y;
	int		gx;
	int		gy;
	int		width;
	int		height;
	float	ct1;
	float	ct2;
	int		bpp;
	int		sizeline;
	int		endian;
	char	*img_addr;
	char	***map;
	int		map_x;
	int		map_y;
	float	alt;
	float	pers;
	float	zoom;
}				t_param;

typedef	struct	s_pix
{
	int				x;
	int				y;
	unsigned int	color;
}				t_pix;

t_param			*init_param(int size_x, int size_y, char *title,
				char *file_name);
void			init_pos(t_param *param);
void			img_put_pixel(t_param *param, int x, int y, unsigned int color);
void			img_draw_line(t_param *param, t_pix p1, t_pix p2);
t_pix			get_pix(t_param *param, int i, int j);
int				create_img(t_param *param);
int				allowed_char(char c);

#endif
