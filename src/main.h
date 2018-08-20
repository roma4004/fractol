/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/20 15:38:19 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024
# define WIN_NAME "Fractol by dromanic (@Dentair)"
# define DEF_COLOR 0x0f9100FF
# define CPU_CORES 8
# define PI 3.14159265359

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <pthread.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
//# include <string.h>

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
	float	zoom;
	float	zoom_x;
	float	zoom_y;
	float	centr_x;
	float	centr_y;
	double	iter_step;
	double	spec_step;
	double	spec1;
	double	spec2;
	double	offset_step;
	double	offset_y;
	double	offset_x;
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
	int		a;
	int		r;
	int		g;
	int		b;
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
	pthread_t child_ptr[CPU_CORES];
}				t_win;

enum			e_offset
{
	ALPHA = 24,
	RED = 16,
	GREEN = 8,
	BLUE = 0
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
	Q = 12, W = 13, E = 14, R = 15,
	A = 0,  S = 1,  D = 2,  F= 3,
	Z = 6,  X = 7,  C = 8,  V = 9,
	 ENTER = 36, ESC = 53,
	ARROW_UP = 126, ARROW_DOWN = 125,
	ARROW_LEFT = 123, ARROW_RIGHT = 124,
	MOUSE_SCROLL_UP = 4, MINUS = 27,
	MOUSE_SCROLL_DOWN = 5, PLUS = 24,
	HOME = 115, END = 119, PAGE_UP = 116, PAGE_DOWN = 121,

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
	BARNSLEY_PART_BODY = 1,
	BARNSLEY_PART_LEFT = 2,
	BARNSLEY_PART_RIGHT = 3,
	BARNSLEY_PART_CURVE = 4,
	FR_MANDELBROT = 1,
};


void		redraw_fract(t_win *win);
int			get_fractal_point(t_win *win, int x, int y);
int			mandelbrot(t_win *win, int x, int y);
int			mandelbrot_cuboid(t_win *win, int x, int y);

t_col		*gen_color(t_win *win, int i);
int			get_color(t_col *col);
int			change_hue(int color, int offset, int mask_offset);
void		change_color(t_win *win, int key);

int			specific_param(t_win *win, int key);
void		draw_fractal(t_win *win);
void		draw_barnsley(t_win *win);

void		init_fract(t_param *param, int id);
t_win		*init_win(void);
t_param		*init_param(void);
t_flags		*init_flags(void);
t_img		*init_img(t_win *win, int width, int height);
t_win		*clear_img(t_win *win);

int			deal_keyboard(int key, t_win *win);
int			deal_mouse(int key, int x, int y, t_win *win);
int			exit_x(t_win *par);

int			zoom(t_win *win, int key, float x, float y);
int			iterate_change(t_win *win, int iter_offset);
void		fractal_switch(t_win *win);
int			map_offset(t_win *win, int key);
void		show_interface(t_win *win);
void		show_errors(t_win *win);

double		pow_of(double num, int exp);
int			toggles(t_win *win, int key);
int			toggle_param(int *param);
void		px_to_img(t_img *img, int x, int y, int color);
void		redraw_img(t_win *win);

void		reset(t_win *win);
int			free_win(t_win *win);

#endif
