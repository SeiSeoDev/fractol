#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

typedef struct	s_img
{
	void		*img_ptr;
	char		*data; 
	int			size_l;
	int			bpp;
	int			endian;
    double START_X;
    double START_Y;
    double ZOOM;

}				t_img;

typedef struct		s_list
{
    int size_x;
    int size_y;
    void *mlx_ptr;
    void *mlx_win;
    char *test_text;
	int mousex;
	int mousey;
	int test;
	double CxMin;
	double CyMin;
	double CxMax;
	double CyMax;
	int iterations;
    t_img		*mlx_img;

}			data_str;

typedef struct		s_complex
{
	float			r;
	float			i;
}					t_complex;

typedef struct		s_rgb
{
	int				r;
	int		    	g;
	int		    	b;
}					t_rgb;

typedef struct		s_hsv
{
	float			h;
	float			s;
	float			v;
}					t_hsv;

int	hsv_to_rgb(t_hsv hsv);
int	rgb_to_int(t_rgb rgb);
int	get_rgb(unsigned char r, unsigned char g, unsigned char b);
void px_to_onscreenimg(data_str *data_strc , int x, int y, int c);
t_complex add_comp(t_complex a, t_complex b);
t_complex square_comp(t_complex a);
t_complex get_complex(float x, float y);
float get_complex_size(t_complex a);
//gcc -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit main.c