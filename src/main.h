/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/12 16:28:12 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_NAME "Fractol by dromanic (@Dentair)"
# define DEFAULT_MENU_COLOR 0x0f9100FF
# define AMOUNT_FRACTALS 5
# define MAX_THREADS 1000

# include <stdlib.h>

# include "../minilibx/mlx.h"
# include "../libft/libft.h"

typedef struct	s_complex_number
{
	double	iter;
	double	r;
	double	rc;
	double	rsq;
	double	rold;
	double	i;
	double	ic;
	double	isq;
	double	iold;
}				t_cnb;

typedef struct	s_coordinates
{
	int		x;
	int		y;
}				t_coords;

typedef struct	s_param
{
	int			fr_id;
	int			cores;
	int			threads;
	long long	i_max;
	long long	i_step;
	float		left_trim;
	float		up_trim;
	float		right_trim;
	float		down_trim;
	float		center_x;
	float		center_y;
	float		ratio;
	double		zoom;
	double		spec_step;
	double		col_step;
	double		spec1;
	double		spec2;
	double		offset_step;
	double		offset_y;
	double		offset_x;
	double		rj_seed;
	double		ij_seed;
	double		alpha_shift;
	double		red_shift;
	double		green_shift;
	double		blue_shift;
}				t_param;

typedef struct	s_flags
{
	unsigned char	n1:1;
	unsigned char	n2:1;
	unsigned char	n3:1;
	unsigned char	n4:1;
	unsigned char	n5:1;
	unsigned char	n6:1;
	unsigned char	n7:1;
	unsigned char	n8:1;
	unsigned char	q:1;
	unsigned char	w:1;
	unsigned char	e:1;
	unsigned char	col_range:1;
	unsigned char	if_carioid:1;
	unsigned char	alt_color:1;
	unsigned char	hints_on:1;
	unsigned char	values_on:1;
	unsigned char	menu_on:1;
	unsigned char	lock_julia:1;
	unsigned char	green_text:1;
}				t_flags;

typedef struct	s_color
{
	long long	a;
	long long	r;
	long long	g;
	long long	b;
}				t_col;

typedef struct	s_img
{
	void	*ptr;
	int		*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	t_col	col;
}				t_img;

typedef struct	s_environment
{
	t_param		*param;
	t_flags		*flags;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	void		(*init_func[AMOUNT_FRACTALS])(t_param *);
}				t_env;

typedef struct	s_pthread_data
{
	t_env	*win;
	int		offset;
}				t_pth_dt;

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
	NUM_8 = 91, EIGHT = 28, MINUS = 27,
	NUM_9 = 92, NINE = 25, PLUS = 24,
	NUM_0 = 82, ZERO = 29, NUM_MINUS = 78,
	NUM_DIV = 75, NUM_MUL = 67, NUM_PLUS = 69,
	MOUSE_SCROLL_UP = 4, MOUSE_LBT = 1,
	MOUSE_SCROLL_DOWN = 5, MOUSE_RBT = 2,
	Q = 12, W = 13, E = 14, R = 15, T = 17, Y = 16, U = 32,
	A = 0, S = 1, D = 2, F = 3, G = 5, H = 4, J = 38,
	Z = 6, X = 7, C = 8, V = 9, B = 11, N = 45, M = 46,
	ENTER = 36, ESC = 53,
	ARROW_UP = 126, ARROW_DOWN = 125,
	ARROW_LEFT = 123, ARROW_RIGHT = 124,
	HOME = 115, PAGE_UP = 116,
	END = 119, PAGE_DOWN = 121
};

enum			e_fr_type
{
	FR_BARNSLEY = 0,
	FR_MANDELBROT = 1,
	FR_BATMAN = 2,
	FR_MANDELBROT_CUBOID = 3,
	FR_JULIA = 4,
	BARNSLEY_PART_BODY = 1,
	BARNSLEY_PART_LEFT = 2,
	BARNSLEY_PART_RIGHT = 3,
	BARNSLEY_PART_CURVE = 4,
};

int				change_color(t_env *env, int key);
void			argb_shift(t_env *env, t_param *param);
int				get_color(t_env *env, int i);

void			redraw_fract(t_env *env, int img_only);
int				get_fractal_col(t_env *env, int x, int y);
void			draw_barnsley(t_env *env);

int				get_mandelbrot_color(t_env *env, int x, int y);
int				get_julia_color(t_env *env, int x, int y);
int				get_batman_color(t_env *env, int x, int y);
int				get_mandelbrot_cuboid_color(t_env *env, int x, int y);

void			init_barnsley(t_param *param);
void			init_mandelbrot(t_param *param);
void			init_batman(t_param *param);
void			init_mandelbrot_cuboid(t_param *param);
void			init_julia(t_param *param);

int				flag_reset(t_flags *flags);
t_img			*init_img(void *mlx_ptr, int width, int height);
t_env			*init_win(void);

int				map_offset(t_env *env, int key, t_param *param);
int				specific_param(t_env *env, int key, t_param *param);
int				iterate_change(t_env *env, int iter_offset);
int				zoom(t_env *env, int key, float x, float y);
int				toggles(t_env *env, int key, t_param *p, t_flags *f);

void			show_menu(t_env *e, int x, int y, t_flags *f);
void			show_combo(t_env *env, int x, int y);
void			show_values(t_env *e, int x, int y);

int				deal_keyboard(int key, t_env *env);
int				deal_mouse(int key, int x, int y, t_env *env);
int				deal_mouse_move(int x, int y, t_env *env);
int				exit_x(t_env *par);

int				free_win(t_env *env);
t_env			*clear_img(t_env *env);
int				exit_x(t_env *win);

int				if_сardioid(t_env *env, double pr, double pi);
int				mandel_break(t_env *env, t_cnb *z);

int				text(t_env *env, int x, int y, char *str);
int				text_green(t_env *env, int x, int y, char *str);

void			px_to_img(t_img *img, int x, int y, int color);
void			parallel_draw_fractal(t_env *env);

#endif
