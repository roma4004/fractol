/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/17 13:41:27 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIN_WIDTH 1920.0f
# define WIN_HEIGHT 1080.0f
# define WIN_NAME "Fractol by dromanic (@Dentair)"
# define DEFAULT_MENU_COLOR 0x0f9100FF
# define ACTIVE_MENU_COLOR 0x00ff00
# define AMOUNT_FRACTALS 5
# define MAX_THREADS 1000

# include <stdlib.h>
# include <stdbool.h>
//todo: # include <complex.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"

typedef struct	s_uint32t_point
{
	u_int32_t	x;
	u_int32_t	y;
}				t_uint_pt;

typedef struct	s_int32t_point
{
	int32_t		x;
	int32_t		y;
}				t_int_pt;

typedef struct	s_float_point
{
	float		x;
	float		y;
}				t_float_pt;

typedef struct	s_double_point
{
	double		x;
	double		y;
}				t_double_pt;

typedef struct	s_complex_number
{
	double	r;
	double	rc;
	double	rsq;
	double	rold;
	double	i;
	double	ic;
	double	isq;
	double	iold;
}				t_cnb;//todo: use build in complex num


typedef struct	s_fractal_triming_side
{
	float		left;
	float		up;
	float		right;
	float		down;
}				t_trim;

typedef struct	s_fractal_color_shift
{
	int			alpha;
	int			red;
	int			green;
	int			blue;
}				t_col_shift;

typedef struct	s_fractal_parameters
{
	int			fr_id;
	int			cores;
	int			threads;
	t_col_shift	col_shift;
	int			depth;
	int			depth_step;
	int			display_zoom;
	float		ratio;
	t_trim		trim;
	t_float_pt	center;
	float		spec1;
	float		spec2;
	float		spec_step;
	float		offset_step;
	double		col_step;
	double		actial_zoom;
	t_double_pt	offset;
	double		r_mouse_move_seed;
	double		i_mouse_move_seed;
}				t_param;

typedef struct	s_fractal_state_flags
{
	bool	n1;
	bool	n2;
	bool	n3;
	bool	n4;
	bool	n5;
	bool	n6;
	bool	n7;
	bool	n8;
	bool	q;
	bool	w;
	bool	e;
	bool	range;
	bool	carioid;
	bool	alt_color;
	bool	hints;
	bool	values;

	bool	menu;
	bool	lock_julia;
}				t_flags;

typedef struct	s_color_channels_argb
{
	int		a;
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct	s_img
{
	void	*ptr;
	int		*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_fract_parse
{
	char	*id;
	char	*name;
}				t_fractals;

typedef struct	s_environment
{
	t_param		*param;
	t_flags		*flags;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	char		*names[AMOUNT_FRACTALS];
	int			(*get_px[AMOUNT_FRACTALS])(struct s_environment *, t_int_pt);
	void		(*init_func[AMOUNT_FRACTALS])(t_param *);
}				t_env;

typedef struct	s_pthread_data
{
	t_env	*env;
	int		offset;
}				t_pth_dt;

enum			e_color_offset
{
	ALPHA = 24,
	RED = 16,
	GREEN = 8,
	BLUE = 0
};

enum			e_keys_code
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

enum			e_fractal_type
{
	FR_MANDELBROT = 0,
	FR_JULIA = 1,
	FR_FERN = 2,
	FR_CUBOID = 3,
	FR_BATMAN = 4,
	BARNSLEY_PART_BODY = 1,
	BARNSLEY_PART_LEFT = 2,
	BARNSLEY_PART_RIGHT = 3,
	BARNSLEY_PART_CURVE = 4,
};

int				change_color(t_env *env, t_col_shift *col_shift, int key);
void			argb_shift(t_env *env, t_col_shift *col_shift);
int				get_color(t_param *param, t_flags *flags, int i);

void			redraw_fract_or_img(t_env *env, t_param *param, int img_only);
int				draw_barnsley(t_env *env, t_int_pt pt);
int				get_mandelbrot(t_env *env, t_int_pt pt);
int				get_julia(t_env *env, t_int_pt pt);
int				get_batman(t_env *env, t_int_pt pt);
int				get_mandelbrot_cuboid(t_env *env, t_int_pt pt);

int				map_offset(t_env *env, int key, t_param *param);
int				specific_param(t_env *env, t_param *param, int key);
int				fr_depth(t_env *env, t_param *param, t_flags *flags, int key);
int				zoom(t_env *env, int key, float x, float y);
int				toggles(t_env *env, int k, t_param *p, t_flags *f);

t_img			*init_img(void *mlx_ptr, float width, float height);
t_env			*init_env(void);

void			init_barnsley(t_param *param);
void			init_mandelbrot(t_param *param);
void			init_batman(t_param *param);
void			init_mandelbrot_cuboid(t_param *param);
void			init_julia(t_param *param);

void			show_menu(t_env *env, t_flags *flags, int x, int y);
void			show_combo(t_env *env, int x, int y);
void			show_values(t_env *env, t_param *param, int x, int y);

int				deal_keyboard(int key, t_env *env);
int				deal_mouse(int key, int x, int y, t_env *env);
int				deal_mouse_move(int x, int y, t_env *env);
int				exit_x(t_env *env);

int				is_cardioid(t_param *param, t_flags *flags, t_cnb *z);
int				mandel_break(t_param *param, t_flags *flags, t_cnb *z);

int				free_win(t_env *env);
t_env			*clear_img(t_env *env);

void			parallel_draw(t_env *env, int threads);

#endif
