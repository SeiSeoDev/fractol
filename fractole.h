typedef struct	s_img
{
	void		*img_ptr;
	int			*data; 
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
    t_img		*mlx_img;

}			data_str;

//gcc -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit main.c