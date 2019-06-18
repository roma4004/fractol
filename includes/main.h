/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 19:41:05 by dromanic          #+#    #+#             */
/*   Updated: 2019/06/18 20:29:51 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define W_WIDTH			1920
# define W_HEIGHT			1080
# define W_NAME				"Fractol by dromanic (@Dentair)"
# define DEFAULT_MENU_COLOR	0x0f9100FF
# define ACTIVE_MENU_COLOR	0x00ff00
# define AMOUNT_FRACTALS	5
# define MAX_THREADS		1000

# define MSG_FRACT_MANDEL	"Mandelbrot"
# define MSG_FRACT_JULIA	"Julia"
# define MSG_FRACT_BARNSL	"Fern"
# define MSG_FRACT_CUBOID	"Cuboid"
# define MSG_FRACT_BATMAT	"Batman"

# define MSG_MENU_SEC		"MENU         :"
# define MSG_ZOOM_M			"zoom         : -, + or mouse scroll"
# define MSG_NEXT_FRA		"next fractal : Enter"
# define MSG_DEPTH			"depth        : num_+, num_- or 9, 0"
# define MSG_DEPTH_STEP		"depth step   : num_/, num_*"
# define MSG_RESET			"reset        : R"
# define MSG_EFFECTS		"effects      :                   (or numpad)"
# define MSG_EFFECTS_1		"1"
# define MSG_EFFECTS_2		"2"
# define MSG_EFFECTS_3		"3"
# define MSG_EFFECTS_4		"4"
# define MSG_EFFECTS_5		"5"
# define MSG_EFFECTS_6		"6"
# define MSG_EFFECTS_7		"7"
# define MSG_EFFECTS_8		"8"
# define MSG_EFFECTS_9		"9"
# define MSG_EFFECTS_Q		"Q"
# define MSG_EFFECTS_E		"E"

# define MSG_CARIOID		"calc carioid :"
# define MSG_CARIOID_Y		"Y"
# define MSG_CARIOID_COL	"white carioid:   (when calc carioid is on)"
# define MSG_CARIOID_W		"W"
# define MSG_STYLE			"color style  :  ,   "
# define MSG_STYLE_T		"T"
# define MSG_STYLE_G		"G"
# define MSG_MOUSE_DET		"mouse detect : mouse_"
# define MSG_MOUSE_DET_R	"R"
# define MSG_THREAD_NUM		"threads num  : (+, -) U, J"
# define MSG_SHIFT_ARGB		"shift ARGB   : (+, -) A, Z,  S, X,  D, C,  F, V"
# define MSG_RADIUS			"radius change: Home, End"
# define MSG_TRIM			"trim change  : Page_Up, Page_Down (for 5 effect)"
# define MSG_CURVE_X		"curve X      : Home, End (for Barnsley)"
# define MSG_CURVE_Y		"curve Y      : Page_Up, Page_Down (for Fern)"
# define MSG_MENU_SW		"menu         : M"
# define MSG_COMBO_SW		"combo        : H"
# define MSG_VALUE_SW		"values       : N"

# define MSG_HINTS			"COMBO HINT:"
# define MSG_BG				"background: r + q + e"
# define MSG_WIND			"wind      : r + q, r + e"
# define MSG_LEAF			"leaf      : r + 4 or num_4"
# define MSG_FLOWER			"flower    : r + 8 or num_8"
# define MSG_CLOUDS			"clouds    : r + 4 or num_4 + 8 or num_8"
# define MSG_BLADES			"blades    : r + 4 + Z (press Z 17 times)"
# define MSG_SHIP			"burn ship : r + 2 + 3 (for Mandelbrot)"
# define MSG_TRICORN		"tricorn   : r + 2 (for Mandelbrot)"
# define MSG_LOHNES			"lohnes    : r + q, e, t)"
# define MSG_HEART			"heart     : r + 3 or num_3"
# define MSG_MIR_HOR		"mirror hor: 6 or num_6"
# define MSG_MIR_VER		"mirror ver: 7 or num_7 (for Ship, Lohnes)"

# define MSG_VAL_SEC		"ACTUAL VALUES  :"
# define MSG_CUR_FRA		"current fractal: "
# define MSG_ITER_LIM		"iteration limit:"
# define MSG_ITER_STE		"iteration step :"
# define MSG_ZOOM			"zoom           :"
# define MSG_THREADS		"threads        :"
# define MSG_SHI_ALF		"shift alpha    :"
# define MSG_SHI_RED		"shift red      :"
# define MSG_SHI_GRE		"shift green    :"
# define MSG_SHI_BLU		"shift blue     :"

# include <stdlib.h>

# pragma GCC diagnostic ignored "-Wstrict-prototypes"
# pragma GCC diagnostic ignored "-Wpadded"
# include "mlx.h"
# pragma GCC diagnostic warning "-Wpadded"
# pragma GCC diagnostic warning "-Wstrict-prototypes"


# include "libft.h"

typedef struct	s_int32t_point
{
	int32_t		x;
	int32_t		y;
}				t_si_pt;

typedef struct	s_uint32t_point
{
	uint32_t	x;
	uint32_t	y;
}				t_ui_pt;

typedef struct	s_double_point
{
	double		x;
	double		y;
}				t_db_pt;

typedef struct	s_complex_number
{
	double		r;
	double		rc;
	double		rsq;
	double		rold;
	double		i;
	double		ic;
	double		isq;
	double		iold;
}				t_cnb;

typedef struct	s_fern_fractal
{
	double		r;
	double		i;
	char		stub[4];
}				t_fern;

typedef struct	s_fractal_triming_side
{
	double		left;
	double		up;
	double		right;
	double		down;
}				t_trim;

typedef struct	s_fractal_color_shift
{
	int		alpha;
	int		red;
	int		green;
	int		blue;
}				t_col_shift;

typedef struct	s_fractal_parameters
{
	t_db_pt			center;
	t_db_pt			offset;
	t_trim			trim;
	t_col_shift		color_shift;
	double			spec_step;
	double			offset_step;
	double			hor;
	double			ver;
	double			color_step;
	double			actial_zoom;
	double			r_move_seed;
	double			i_move_seed;
	unsigned int	fr_id;
	unsigned int	cores;
	unsigned int	threads;
	unsigned int	depth;
	int				depth_step;
	int				display_zoom;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	char			stub[4];
}				t_param;

typedef struct	s_fractal_state_flags
{
	_Bool	n1;
	_Bool	n2;
	_Bool	n3;
	_Bool	n4;
	_Bool	n5;
	_Bool	n6;
	_Bool	n7;
	_Bool	n8;
	_Bool	n9;
	_Bool	n0;
	_Bool	q;
	_Bool	w;
	_Bool	e;
	_Bool	range;
	_Bool	carioid;
	_Bool	alt_col;
	_Bool	hints;
	_Bool	values;
	_Bool	menu;
	_Bool	lock_julia;
}				t_flags;

typedef struct	s_color_channels_argb
{
	unsigned int	a;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}				t_color;

typedef unsigned int __attribute__
((__aligned__(1),__may_alias__))	t_uint32_unalign;

typedef struct	s_environment
{
	t_param			param;
	t_flags			flags;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned int	*surf;
	char			*fract_names[AMOUNT_FRACTALS];
	unsigned int	(*get_px_func[AMOUNT_FRACTALS])
					(struct s_environment const *restrict,
							t_param, size_t, size_t);
	void			(*init_func[AMOUNT_FRACTALS])(t_param *);
}				t_env;

typedef struct	s_pthread_data
{
	t_env const		*env;
	size_t			offset;
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
	ENTER = 36, ESC = 53, I = 34, O = 31,
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
};

/*
** color.c
*/

unsigned int	change_color(t_env *restrict env,
								t_col_shift *restrict col_shift, int key);
void			argb_shift(t_env const *restrict env, t_col_shift shift);
unsigned int	get_color(bool alt_col, double col_step,
							unsigned int depth, unsigned int i);

/*
** draw.c
*/

unsigned int	redraw_fract_or_img(t_env const *restrict env, t_param param,
									t_flags flags, int img_only);
unsigned int	draw_barnsley(t_env const *restrict env, t_param p,
								size_t x, size_t y);
void			parallel_draw(t_env const *restrict env, unsigned int threads);

/*
** fractals.c
*/

unsigned int	get_mandelbrot(t_env const *restrict env, t_param p,
								size_t x, size_t y);
unsigned int	get_julia(t_env const *restrict env,
							t_param p, size_t x, size_t y);
unsigned int	get_batman(t_env const *restrict env,
							t_param p, size_t x, size_t y);
unsigned int	get_mandelbrot_cuboid(t_env const *restrict env,
										t_param p, size_t x, size_t y);

/*
** keys.c
*/

unsigned int	map_offset(t_env *restrict env, int key,
							t_param param, t_db_pt *restrict offset);
unsigned int	specific_param(t_env *restrict env, t_param *restrict param,
								int key);
unsigned int	fr_depth(t_env *restrict env, t_param *restrict param,
							bool range, int key);
unsigned int	zoom(t_env *restrict env, int key, t_db_pt pt);
unsigned int	toggles(t_env *restrict env, int key,
						t_param *restrict p, t_flags *restrict f);

/*
** init.c
*/

t_env			*init_env(t_env *restrict env);

/*
** init_fractals.c
*/

void			init_barnsley(t_param *restrict param);
void			init_mandelbrot(t_param *restrict param);
void			init_batman(t_param *restrict param);
void			init_mandelbrot_cuboid(t_param *restrict param);
void			init_julia(t_param *restrict param);

/*
** interface.c
*/

void			show_menu(t_env const *restrict env, t_flags flags,
							int x, int y);
void			show_combo(t_env const *restrict env, bool menu, int x, int y);
void			show_values(t_env const *restrict env, t_param p, int x, int y);

/*
** hooks.c
*/

int				deal_keyboard(int key, t_env *restrict env);
int				deal_mouse(int key, int x, int y, t_env *restrict env);
int				deal_mouse_move(int x, int y, t_env *restrict env);
int				exit_x(t_env *restrict env);

/*
** main.c
*/

int				is_cardioid(t_flags flags, t_cnb *restrict z);
int				mandel_break(t_param p, t_flags flags, t_cnb *restrict z);

#endif
