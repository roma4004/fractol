/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 17:38:40 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIN_WIDTH 1920.0f
# define WIN_HEIGHT 1080.0f
# define WIN_NAME "Fractol by dromanic (@Dentair)"
# define DEFAULT_MENU_COLOR 0x0f9100FF
# define AMOUNT_FRACTALS 5
# define MAX_THREADS 1000

# include <stdlib.h>

# include "../minilibx/mlx.h"
# include "../libft/libft.h"

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
}				t_cnb;

typedef struct	s_fractal_parameters
{
	int		fr_id;
	int		cores;
	int		threads;
	int		alpha_shift;
	int		red_shift;
	int		green_shift;
	int		blue_shift;
	int		fr_depth;
	int		fr_depth_step;
	int		display_zoom;
	float	ratio;
	float	left_trim;
	float	up_trim;
	float	right_trim;
	float	down_trim;
	float	center_x;
	float	center_y;
	float	spec1;
	float	spec2;
	float	spec_step;
	float	offset_step;
	double	col_step;
	double	actial_zoom;
	double	offset_y;
	double	offset_x;
	double	r_mouse_move_seed;
	double	i_mouse_move_seed;
}				t_param;

typedef struct	s_fractal_state_flags
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
	unsigned char	hints_off:1;
	unsigned char	values_off:1;
	unsigned char	menu_off:1;
	unsigned char	lock_julia:1;
	unsigned char	green_text:1;
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

int				change_color(t_env *env, t_param *param, int key);
void			argb_shift(t_env *env, t_param *param);
int				get_color(t_param *param, t_flags *flags, int i);

void			redraw_fract(t_env *env, int img_only);
int				get_fractal_color(t_param *param, t_flags *flags, int x, int y);
void			draw_barnsley(t_env *env, t_param *par);

int				get_mandelbrot(t_param *param, t_flags *flags, int x, int y);
int				get_julia(t_param *param, t_flags *flags, int x, int y);
int				get_batman(t_param *param, t_flags *flags, int x, int y);
int				get_mandelbrot_cuboid(t_param *param, t_flags *flags,
										int x, int y);

int				map_offset(t_env *env, int key, t_param *param);
int				specific_param(t_env *env, t_param *param, int key);
int				fr_depth(t_env *env, t_param *param, t_flags *flags, int key);
int				zoom(t_env *env, int key, float x, float y);
int				toggles(t_env *env, int key, t_param *p, t_flags *f);

int				flag_reset(t_flags *flags);
t_img			*init_img(void *mlx_ptr, float width, float height);
t_env			*init_env(void);

void			init_barnsley(t_param *param);
void			init_mandelbrot(t_param *param);
void			init_batman(t_param *param);
void			init_mandelbrot_cuboid(t_param *param);
void			init_julia(t_param *param);

void			show_menu(t_env *env, int x, int y, t_flags *flags);
void			show_combo(t_env *env, int x, int y);
void			show_values(t_env *env, int x, int y);

char			*text(t_env *env, int x, int y, char *str);
char			*text_green(t_env *env, int x, int y, char *str);
int				deal_keyboard(int key, t_env *env);
int				deal_mouse(int key, int x, int y, t_env *env);
int				deal_mouse_move(int x, int y, t_env *env);
int				exit_x(t_env *env);

int				is_cardioid(t_param *param, t_flags *flags, t_cnb *z);
int				mandel_break(t_param *param, t_flags *flags, t_cnb *z);

int				free_win(t_env *env);
void			clear_img(t_env *env);

void			px_to_img(t_img *img, int x, int y, int color);
void			parallel_draw_fractal(t_env *env);

#endif
