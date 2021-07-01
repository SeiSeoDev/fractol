#include "mlx/mlx.h"
#include "fractole.h"

void px_put(data_str *data_strct, int color)
{
    int x;
    int y;
    
    x = 0;

    while (x < 1920)
    {
        y = 0;
        while (y < 1080)
        {
            mlx_pixel_put(data_strct->mlx_ptr, data_strct->mlx_win, x, y, color);
            y++;
        }
        x++;
    }
}
int text_size(char *addr)
{
    int fd;
    char *osef;
    int count;
    fd = open(addr, O_RDONLY);
    
    while (read(fd, osef, 1) > 0)
        count++;
    close(fd);
    printf("%d\n", count);
    return(count);
}
char *get_xpm(char *addr)
{
    int fd;
    int buf_size;
    char *text_data_strct;
    buf_size = text_size(addr);
    text_data_strct = malloc(sizeof(char) * (1 + buf_size));
    fd = open(addr, O_RDONLY);

    read(fd, text_data_strct, buf_size);
    text_data_strct[buf_size] = '\0';
    //printf("%s\n", text_data_strct);
return (text_data_strct);
}

void print_color(data_str *data_strct, unsigned char *color, int x, int y)
{
    /*char convert[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', };
    int cnt = 0;
    char tmp[9];
    char swap;
    tmp[8] = 0;
    tmp[0] = '0';
    tmp[1] = 'x';
    for (int i=0; i < 3; i++)
    {    
        tmp[2 * (i + 1)] = 0;
        tmp[2 * (i + 1) + 1] = 0;
        if (color[i] == 0)
        {
            tmp[2 + cnt++] = '0';
            tmp[2 +cnt++] = '0';
        }
        while(color[i] > 0)
        {
            //data_strct->mlx_img->data[(1920 * y) + (x)] += color[i] % 16;
            tmp[2+cnt++] = convert[color[i]%16];
            color[i] /=  16;
        }
        if (cnt < 2*(i + 1))
            tmp[cnt++] = '0';
        swap = tmp[2 * (i+ 1)];
        tmp[2*(i + 1)] = tmp[2*(i + 1)+1];
        tmp[2* (i + 1)+1] = swap;
    }*/
    *(int *)(data_strct->mlx_img->data + ((y * 1920 + x) * data_strct->mlx_img->bpp/32))= color[0] * 256 *256 + color[1] * 256 + color[2];
    //my_mlx_pixel_put(data_strct->mlx_img, x, y, "0xFFFFFF");
    //printf("%s ||", tmp);
  //  printf("%d\n", data_strct->mlx_img->data[(1920 * y) + (x)]);
}
t_hsv mandelbrot(t_complex z, t_complex c, data_str *data_strct, int iteration_max)
{
    int i;
    t_hsv color;
    i = 0;

    for (i = 0; i < iteration_max && get_complex_size(z) < 4; i++)
    {
        z = add_comp(square_comp(z), c);
    }

    if (i == iteration_max)
    {
        color.h = 0;
        color.s = 0;
        color.v = 0;
        return (color);
    }
    color.h = 50;
    color.s = 50+i/5;                   
    color.v = i;
    return (color);

}
void print_fract(data_str *data_strct)
{
        clock_t start, stop;
       // Tableau temporaire pour une ligne de pixels
    unsigned char line_buffer[data_strct->size_x * 3];

        unsigned char color[3];
        double mx, my, x, y, x2, y2;

        /* world ( double) coordinate = parameter plane*/
        double Cx,Cy;
        const double CxMin= -4;
        const double CxMax= 3;
        const double CyMin= -2.0;
        const double CyMax= 2.0;
        int iX,iY;
        t_hsv hsv;
        hsv.s = 71;
        hsv.v = 90;
        double Zx, Zy;
        const int iXmax = 1920; 
        const int iYmax = 1080;
        double Zx2, Zy2; 
        int Iteration;
        const int IterationMax=100;
        const double EscapeRadius=2;
        double ER2=EscapeRadius*EscapeRadius;
                double PixelWidth=(CxMax-CxMin)/iXmax;
        double PixelHeight=(CyMax-CyMin)/iYmax;
        int i;
        for( iY = 0;iY<iYmax;iY++)
        {
            Cy = iY / (float)iYmax * (4) * data_strct->mlx_img->ZOOM + CyMin;
             for(iX=0;iX<iXmax;iX++)
             {       
                 Cx = iX / (float)iXmax * (7) * data_strct->mlx_img->ZOOM + CxMin;
                        px_to_onscreenimg(data_strct, iX, iY, hsv_to_rgb(mandelbrot(get_complex(0, 0), get_complex(Cx, Cy), data_strct, IterationMax))); 
            }
        }
        mlx_put_image_to_window(data_strct->mlx_ptr, data_strct->mlx_win, data_strct->mlx_img->img_ptr, 0, 0);

}

int mouse_hook(int button,int x,int y,data_str *data_strct){
    printf("button : %d | x : %d | y : %d\n", button, x, y);
    printf("startX : %f | startY : %f\n", data_strct->mlx_img->START_X, data_strct->mlx_img->START_Y);
    if (button == 4)
        {
        data_strct->mlx_img->ZOOM += 1;
        data_strct->mlx_img->START_Y = 1.5 * (x - data_strct->size_x / 2.0) / (0.5 * data_strct->mlx_img->ZOOM * data_strct->size_x) + 1080;
        data_strct->mlx_img->START_X = (y - data_strct->size_y / 2.0) / (0.5 * data_strct->mlx_img->ZOOM * data_strct->size_y) + 1920;

        }
    if (button == 5)
    {
        data_strct->mlx_img->ZOOM -= 0.1;
       // data_strct->mlx_img->START_X = x;
        //data_strct->mlx_img->START_Y = y;
    }
    if (button == 1)
    {
        data_strct->mlx_img->START_X = 1.5 * (x - data_strct->size_x / 2.0) / (0.5 * data_strct->mlx_img->ZOOM * data_strct->size_x);
        data_strct->mlx_img->START_Y = (y - data_strct->size_y / 2.0) / (0.5 * data_strct->mlx_img->ZOOM * data_strct->size_y);
        
    }
    print_fract(data_strct);
    return (1);
}
int main()
{
    data_str *data_strct;
    void *param;
    int count_h, count_w;
    count_h = -1;
    char *str;
    if (!(data_strct = malloc(sizeof(data_str))))
		return (0);
    if (!(data_strct->mlx_img = malloc(sizeof(t_img))))
		return (0);
    data_strct->size_x = 1920;
    data_strct->size_y = 1080;
    data_strct->mlx_img->START_X = 0;
    data_strct->mlx_img->START_Y = 0.0;
    data_strct->mlx_img->ZOOM = 0.8;
    data_strct->mlx_ptr = mlx_init();
    data_strct->mlx_win = mlx_new_window(data_strct->mlx_ptr, data_strct->size_x, data_strct->size_y, "new Window");
    //px_put(data_strct, 9845840);
    data_strct->mlx_img->img_ptr = mlx_new_image(data_strct->mlx_ptr , data_strct->size_x, data_strct->size_y);
    data_strct->mlx_img->data = (char *)mlx_get_data_addr(data_strct->mlx_img->img_ptr, &data_strct->mlx_img->bpp, &data_strct->mlx_img->size_l,
		&data_strct->mlx_img->endian);
    printf("bpp %d, size %d\n", data_strct->mlx_img->bpp, data_strct->mlx_img->size_l);
    /*while (++count_h < 1080)
	{
		count_w = -1;
		while (++count_w < 1920)
		{
			if (count_w % 2)
				
				 As you can see here instead of using the mlx_put_pixel function
				 I just assign a color to each pixel one by one in the image,
				 and the image will be printed in one time at the end of the loop.
				 Now one thing to understand here is that you're working on a 1-dimensional
				 array, while your window is (obviously) 2-dimensional.
				 So, instead of having data[height][width] here you'll have the following
				 formula : [current height * max width + current width] (as you can see below)
				
				data_strct->mlx_img.data[count_h * 1920 + count_w] = 0xFFFFFF;
			else
				data_strct->mlx_img.data[count_h * 1920 + count_w] = 0;
		}
	}*/
    print_fract(data_strct);
    mlx_put_image_to_window(data_strct->mlx_ptr, data_strct->mlx_win, data_strct->mlx_img->img_ptr, 0, 0);

    //str = get_xpm("test.xpm");
    //printf("%s\n", str);
    //printf("%lu\n", strlen(str)); 
    mlx_mouse_hook(data_strct->mlx_win, mouse_hook, data_strct);
    mlx_loop(data_strct->mlx_ptr);
    return (1);
}