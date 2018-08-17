/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/17 20:49:44 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define DEF_OFFSET_Y 0
# define DEF_OFFSET_X 0
# define WIN_NAME "Fractol by dromanic (@Dentair)"
# define DEF_COLOR 0x0f9100FF
# define PI 3.14159265359

# define DEF_BARNSLEY_CURVE_X 0.04
# define DEF_BARNSLEY_CURVE_Y 0.85

# include <stdio.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <string.h>
# include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

typedef struct		s_complex_number
{
	double			newR;
	double			oldR;
	double			newI;
	double			oldI;

}					t_cnb;

typedef struct		s_coordinate_iterator
{
	int				x;
	int				y;
}					t_coords;

typedef struct	s_param
{
	int		fr_id;
	int		iter;
	int		color;
	int		color_step;
	float	zoom;
	float	zoom_x;
	float	zoom_y;
	float	spec1;
	float	spec2;
	float	offset_step;

	float	offset_y;
	float	offset_x;
	float	centr_x;
	float	centr_y;
}				t_param;

typedef struct	s_flags
{
	int		man_1;
	int		man_2;
	int		man_3;
	int		man_4;
	int		man_5;
	int		man_6;
	int		man_7;
	int		interface_on;
	int		error_code;
}				t_flags;

typedef struct	s_color
{
	int	a;
	int	r;
	int	g;
	int	b;
	int	a_offset;
	int	r_offset;
	int	g_offset;
	int	b_offset;
}				t_col;

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	t_col	col;
	float	ratio;
}				t_img;

typedef struct	s_win
{
	t_param	*param;
	t_flags	*flags;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
}				t_win;

enum			e_offset
{
	ALPHA_OFF = 24;
	RED_OFF = 16;
	GREEN_OFF = 8;
	BLUE_OFF = 0;
};

enum			e_keys
{
	NUM_1 = 83, ONE = 18,
	NUM_2 = 84, TWO = 19,
	NUM_3 = 85, THREE = 20,
	NUM_4 = 86, FOUR = 21,
	NUM_5 = 87, FIVE = 23,
	NUM_6 = 88, SIX = 22,
	NUM_7 = 89, SEVEN = 26,
	NUM_8 = 91, EIGHT = 28,
	NUM_MINUS = 78, NINE = 25,
	NUM_PLUS = 69, ZERO = 29,
	Q = 12, W = 13, E = 14,
	A = 0, S = 1, D = 2,
	R = 15, ENTER = 36, ESC = 53,
	ARROW_UP = 126, ARROW_DOWN = 125,
	ARROW_LEFT = 123, ARROW_RIGHT = 124,
	MOUSE_SCROLL_UP = 4, MINUS = 27,
	MOUSE_SCROLL_DOWN = 5, PLUS = 24,
};

enum			e_errors
{
	MAP_INVALID = 404,
	WIDTH_ERR = 405,
	READ_ERR = 406,
	COLOR_ERR = 407,
};

enum			e_fr_type
{
	FR_BARNSLEY = 0,
	FR_MANDELBROT = 1,
};

void	init_fract(t_win *win);
void	redraw_fract(t_win *win);
int		get_fractal_point(t_win *win, t_coords *indexs);
int		mandelbrot(t_win *win, t_coords *indexs);
int		mandelbrot_cuboid(t_win *win, t_coords *indexs);
void	fr_zoom(t_win *win, float zm_offset, int x, int y);
void	iterate_change(t_win *win, int iter_offset);
void	redraw_fract(t_win *win);
t_col	*gen_color(t_win *win, int i);
int		get_color(t_col *col);
int inc_color(int color, int offset);
void	specific_param1(t_win *win, double spec1_offset);
void	specific_param2(t_win *win, double spec2_offset);
void	barnsley_curve(t_win *win, double curve_offset);
void	draw_fractal(t_win *win);
void	draw_barnsley(t_win *win);

double pow_of(double num, int exp);
void			map_offset(t_win *win, double offset_x, double offset_y);
void			fractal_switch(t_win *win);


t_win			*init_win(void);
t_param			*init_param(void);
t_flags			*init_flags(void);
t_img			*init_img(t_win *win, int width, int height);

int				deal_keyboard(int key, t_win *win);
int				deal_mouse(int key, int x, int y, t_win *win);
int				exit_x(t_win *par);

void			show_interface(t_win *win);
void			toggles(t_win *win, int key);
int				toggle_param(int *param);

void			reset(t_win *win);
int				free_win(t_win *win);

#endif
