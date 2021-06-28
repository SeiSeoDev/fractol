#include "mlx/mlx.h"
#include "fractole.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include<time.h>

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


void print_fract(data_str *data_strct)
{
        clock_t start, stop;
       // Tableau temporaire pour une ligne de pixels
    unsigned char line_buffer[data_strct->size_x * 3];
    const unsigned int COLOR_TABLE[] = {
    0xf7df, 0xff5a, 0x07ff, 0x7ffa, 0xf7ff, 0xf7bb, 0xff38, 0xff59, 0x001f, 0x895c, 
    0xa145, 0xddd0, 0x5cf4, 0x7fe0, 0xd343, 0xfbea, 0x64bd, 0xffdb, 0xd8a7, 0x07ff, 
    0x0011, 0x0451, 0xbc21, 0xad55, 0x0320, 0xbdad, 0x8811, 0x5345, 0xfc60, 0x9999, 
    0x8800, 0xecaf, 0x8df1, 0x49f1, 0x2a69, 0x067a, 0x901a, 0xf8b2, 0x05ff, 0x6b4d, 
    0x1c9f, 0xd48e, 0xb104, 0xffde, 0x2444, 0xf81f, 0xdefb, 0xffdf, 0xfea0, 0xdd24, 
    0x8410, 0x0400, 0xafe5, 0xf7fe, 0xfb56, 0xcaeb, 0x4810, 0xfffe, 0xf731, 0xe73f, 
    0xff9e, 0x7fe0, 0xffd9, 0xaedc, 0xf410, 0xe7ff, 0xffda, 0xd69a, 0x9772, 0xfdb8, 
    0xfd0f, 0x2595, 0x867f, 0x839f, 0x7453, 0xb63b, 0xfffc, 0x07e0, 0x3666, 0xff9c, 
    0xf81f, 0x8000, 0x6675, 0x0019, 0xbaba, 0x939b, 0x3d8e, 0x7b5d, 0x07d3, 0x4e99, 
    0xc0b0, 0x18ce, 0xf7ff, 0xff3c, 0xff36, 0xfef5, 0x0010, 0xffbc, 0x8400, 0x6c64, 
    0xfd20, 0xfa20, 0xdb9a, 0xef55, 0x9fd3, 0xaf7d, 0xdb92, 0xff7a, 0xfed7, 0xcc27, 
    0xfe19, 0xdd1b, 0xb71c, 0x8010, 0xf800, 0xbc71, 0x435c, 0x8a22, 0xfc0e, 0xf52c, 
    0x2c4a, 0xffbd, 0xa285, 0xc618, 0x867d, 0x6ad9, 0x7412, 0xffdf, 0x07ef, 0x4416, 
    0xd5b1, 0x0410, 0xddfb, 0xfb08, 0x471a, 0xec1d, 0xd112, 0xf6f6, 0xffff, 0xf7be, 
    0xffe0, 0x9e66, 0x0000
};

    // Pour chaque pixel en Y
    start = clock();
    // int x, y, i;
    // double x2, y2, new_x, new_y, c, v;

    // x = 0;
    // while (y < data_strct->size_x)
    // {
    //     x = 0;
    //     y2 = (2/data_strct->size_x) * y - 1 + data_strct->mlx_img->START_Y * (2/data_strct->size_x) - 1;
    //     while (x < data_strct->size_y)
    //     { 
    //         x2 = (3.5/data_strct->size_y) * x - 1 + data_strct->mlx_img->START_X * (3.5/data_strct->size_y) - 1;
    //         i = 142;
    //         c = 0;
    //         v = 0;
    //         while (i > 0 && c * c + v * v <= 2*2)
    //         {
    //             new_x = c*c-v*v + x2;
    //             v = 2*c*v + y2;
    //             c = new_x;
    //             i--;
    //         }
    //         data_strct->mlx_img->data[y * 1920 + x] =  COLOR_TABLE[142 - i];
    //         x++;
    //     }
    //     y++;
    // }
        for (unsigned int y = 0; y < data_strct->size_y; ++y) {
        double p_i = (y - data_strct->size_y / 2.0) / (0.5 * data_strct->mlx_img->ZOOM * data_strct->size_y) + data_strct->mlx_img->START_Y;
        
        // Pour chaque pixel en X
        for (unsigned int x = 0; x < data_strct->size_x; ++x) {
            double p_r = 1.5 * (x - data_strct->size_x / 2.0) / (0.5 * data_strct->mlx_img->ZOOM * data_strct->size_x) + data_strct->mlx_img->START_X;
            double new_r = 0, new_i = 0, old_r = 0, old_i = 0;
            unsigned int i = 0;
            while ((new_r * new_r + new_i * new_i) < 4.0 && i < 142) {
                old_r = new_r;
                old_i = new_i;
                new_r = old_r * old_r - old_i * old_i + p_r;
                new_i = 2.0 * old_r * old_i + p_i;
                ++i;
            }

            // Dessine le pixel (avec conversion RGB565 -> RGB565)
            unsigned int color = COLOR_TABLE[i];
            data_strct->mlx_img->data[(1920 * y) + (x)] = color;
        }
   //             printf("tests : %f", p_i);
        // Sauvegarde la ligne de pixels dans le fichier PPM
        }
// for each pixel (Px, Py) on the screen do
//     x0 := scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
//     y0 := scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
//     x := 0.0
//     y := 0.0
//     iteration := 0
//     max_iteration := 1000
//     while (x*x + y*y ≤ 2*2 AND iteration < max_iteration) do
//         xtemp := x*x - y*y + x0
//         y := 2*x*y + y0
//         x := xtemp
//         iteration := iteration + 1
 
//     color := palette[iteration]
//     plot(Px, Py, color)
/*
    for (unsigned int y = 0; y < data_strct->size_y; ++y) {
        double p_i = (y - data_strct->size_y / 2.0) / (0.5 * data_strct->mlx_img->ZOOM * data_strct->size_y) + data_strct->mlx_img->START_Y;
        
        // Pour chaque pixel en X
        for (unsigned int x = 0; x < data_strct->size_x; ++x) {
            double p_r = 1.5 * (x - data_strct->size_x / 2.0) / (0.5 * data_strct->mlx_img->ZOOM * data_strct->size_x) + data_strct->mlx_img->START_X;
            double new_r = 0, new_i = 0, old_r = 0, old_i = 0;
            unsigned int i = 0;

            // Magie noir mathématique (merci Wikipedia)
            while ((new_r * new_r + new_i * new_i) < 4.0 && i < 142) {
                old_r = new_r;
                old_i = new_i;
                new_r = old_r * old_r - old_i * old_i + p_r;
                new_i = 2.0 * old_r * old_i + p_i;
                ++i;
            }

            // Dessine le pixel (avec conversion RGB565 -> RGB565)
            unsigned int color = COLOR_TABLE[i];
            data_strct->mlx_img->data[(1920 * y) + (x)] = color;
        }
        
        // Sauvegarde la ligne de pixels dans le fichier PPM
        }
stop = clock();
  */  mlx_put_image_to_window(data_strct->mlx_ptr, data_strct->mlx_win, data_strct->mlx_img->img_ptr, 0, 0);

 //   printf("temps d execution en sec %lu\n", (stop - start)*1000/CLOCKS_PER_SEC);
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
    data_strct->mlx_img->data = (int *)mlx_get_data_addr(data_strct->mlx_img->img_ptr, &data_strct->mlx_img->bpp, &data_strct->mlx_img->size_l,
		&data_strct->mlx_img->endian);
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