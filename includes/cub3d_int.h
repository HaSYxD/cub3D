#ifndef CUB3D_INT_H
# define CUB3D_INT_H

//FRAMEWORK TYPES---------//

# define MLX_RED	(struct s_color){255, 255, 0, 0}
# define MLX_GREEN	(struct s_color){255, 0, 255, 0}
# define MLX_BLUE	(struct s_color){255, 0, 0, 255}
# define MLX_WHITE	(struct s_color){255, 255, 255, 255}
# define MLX_LGRAY	(struct s_color){255, 150, 150, 150}
# define MLX_DGRAY	(struct s_color){255, 50, 50, 50}
# define MLX_BLACK	(struct s_color){255, 0, 0, 0}

# define MAX_TXTBOX_LEN	128
# define FONT	"-sony-fixed-medium-r-normal--24-230-75-75-c-120-iso8859-1"

enum	e_button_type
{
	TOGGLE,
	PUSH
};

typedef struct s_count
{
	int	i;
	int	j;
	int	k;
}	t_count;
//to use when multiple counter variales are needed (save lines)

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;
//to use when working with 2D coordonnates or sizes

typedef struct s_rec
{
	float	x;
	float	y;
	int	width;
	int	height;
}	t_rec;
//to use for representing any rectangle in memory

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;
//to use when working with colors

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;
//standard components needed for mlx images

typedef struct s_txtbox
{
	t_rec	body;
	char	*title;
	char	txt[MAX_TXTBOX_LEN];
}	t_txtbox;
//for inputing text on screen

typedef struct s_button
{
	t_rec	body;
	int	state;
	char	*title;
	int	type;
}	t_button;
//interactive rectangle
//------------------------//

#endif
