/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/09 20:09:44 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
///menu
///6, 7 mirroring fractals
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
//# define WIN_CENTER_X WIN_WIDTH / 2.0
//# define WIN_CENTER_Y WIN_HEIGHT / 2.0
//# define WIN_RATIO WIN_WIDTH / WIN_HEIGHT
# define WIN_NAME "Fractol by dromanic (@Dentair)"
# define DEF_COLOR 0x0f9100FF
# define AMOUNT_FRACTALS 5
//# define CPU_CORES 8
# define ALMOST_HYPER_THREADING 1

# define PI 3.14159265359

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <pthread.h>

/* on macOS detecting number of processors on machine:
 * <sys/param.h>, <sys/sysctl.h> needed for int		func get_processors_num();
 */
# include <sys/param.h>
# include <sys/sysctl.h>

/* on linux detecting number of processors on machine:
 * #include <sys/sysinfo.h>
 * and using:
 * 	{
 * 		return (sysconf(_SC_NPROCESSORS_ONLN));
 * 	}
 */

/* on win32 detecting number of processors on machine:
 * 	{
 * 		SYSTEM_INFO		sysinfo;
 * 		GetSystemInfo(&sysinfo);
 * 		return (sysinfo.dwNumberOfProcessors);
 * 	}
 */

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
//# include <string.h>

typedef struct		s_complex_number
{
	double	iter;
	double	R;
	double	cR;
	double	sqR;
	double	I;
	double	cI;
	double	sqI;

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
	int		iter_step;
	int		cpu_cores;
	int		txt_offset_x;
	int		txt_offset_y;
	float	zoom;
	float	center_x;
	float	center_y;
	double	ratio;
	double	spec_step;
	double	color_step;
	double	spec1;
	double	spec2;
	double	offset_step;
	double	offset_y;
	double	offset_x;
	double	seed_jR;
	double	seed_jI;

}				t_param;

typedef struct	s_flags
{
	int		n1;
	int		n2;
	int		n3;
	int		n4;
	int		n5;
	int		n6;
	int		n7;
	int		n8;
	int		Q;
	int		W;
	int		E;
	int		T;
	int		Y;
	int		G;
	int		Hints_on;
	int		Values_on;
	int		Menu_on;
	int		error_code;
	int		lock_julia;
}				t_flags;

typedef struct	s_color
{
	int		a;
	int		r;
	int		g;
	int		b;
}	t_col;

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
	Q = 12, W = 13, E = 14, R = 15, T = 17, Y = 16,
	A = 0 , S = 1 , D = 2 , F = 3 , G = 5, H = 4,
	Z = 6 , X = 7 , C = 8 , V = 9 , B = 11, N = 45, M = 46,
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

enum			e_iter_color
{
	GRAY = 51,
	WHITE = 129,
	BLACK_N_WHITE = 120,
	BLUE_GREEN = 127,
	BLUE_BLACK = 253,
};


void		redraw_fract(t_env *env);
int			get_fractal_col(t_env *env, int x, int y);
int			mandelbrot_col(t_env *env, int x, int y);
int			mandelbrot_cuboid(t_env *env, int x, int y);
int			batman_col(t_env *env, int x, int y);
int			julia_col(t_env *env, int x, int y);

int			get_color(t_env *env, int i);
int			change_color(t_env *env, int key);

int			specific_param(t_env *env, int key);
void		draw_fractal(t_env *env);
void		draw_barnsley(t_env *env);

t_env		*init_win(void);
t_img		*init_img(void *mlx_ptr, int width, int height);
void		flag_reset(t_flags *flags);

void		init_barnsley(t_param *param);
void		init_mandelbrot(t_param *param);
void		init_batman(t_param *param);
void		init_mandelbrot_cuboid(t_param *param);
void		init_julia(t_param *param);

t_env		*clear_img(t_env *env);

int			deal_keyboard(int key, t_env *env);
int			deal_mouse(int key, int x, int y, t_env *env);
int			deal_mouse_move(int x, int y, t_env *env);
int			exit_x(t_env *par);

int			zoom(t_env *env, int key, float x, float y);
int			iterate_change(t_env *env, int iter_offset);
int			map_offset(t_env *env, int key);

void		show_menu(t_env *env, int x, int y);
void		show_combo(t_env *env, int x, int y);
void		show_value(t_env *env, int x, int y);
void		show_errors(t_env *env);

int			if_сardioid(t_env *env, double pr, double pi);
int			mandel_break(t_env *env, t_cnb *z);
double		pow2(double num, int exp);
int			toggles(t_env *env, int key, t_param *p, t_flags *f);
int			toggle_par(int *param);
void		px_to_img(t_img *img, int x, int y, int color);
void		redraw_img(t_env *env);
int			get_processors_num(void);

void		parallel_draw_fractal(t_env *env);
void		reset(t_env *env);
int			free_win(t_env *env);

#endif
