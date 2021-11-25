#include "fractole.h"
#include "../mlx/mlx.h"

void px_put(data_str *env, int color)
{
    int x;
    int y;
    
    x = 0;

    while (x < env->size_x)
    {
        y = 0;
        while (y < env->size_y)
        {
            mlx_pixel_put(env->mlx_ptr, env->mlx_win, x, y, color);
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
    char *text_env;
    buf_size = text_size(addr);
    text_env = malloc(sizeof(char) * (1 + buf_size));
    fd = open(addr, O_RDONLY);

    read(fd, text_env, buf_size);
    text_env[buf_size] = '\0';
    //printf("%s\n", text_env);
return (text_env);
}

void print_color(data_str *env, unsigned char *color, int x, int y)
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
            //env->mlx_img->data[(1920 * y) + (x)] += color[i] % 16;
            tmp[2+cnt++] = convert[color[i]%16];
            color[i] /=  16;
        }
        if (cnt < 2*(i + 1))
            tmp[cnt++] = '0';
        swap = tmp[2 * (i+ 1)];
        tmp[2*(i + 1)] = tmp[2*(i + 1)+1];
        tmp[2* (i + 1)+1] = swap;
    }*/
    *(int *)(env->mlx_img->data + ((y * 1920 + x) * env->mlx_img->bpp/32))= color[0] * 256 *256 + color[1] * 256 + color[2];
    //my_mlx_pixel_put(env->mlx_img, x, y, "0xFFFFFF");
    //printf("%s ||", tmp);
  //  printf("%d\n", env->mlx_img->data[(1920 * y) + (x)]);
}
t_hsv mandelbrot(t_complex z, t_complex c, data_str *env, int iteration_max)
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
    color.h = 240;
    color.s = i*3;                
    color.v = 100;
    return (color);

  /*  if (i < iteration_max/4)
    {
        color.h = 0;
        color.s = 100;
        color.v = 55;
        return (color);
    }

    if (i == iteration_max)
    {
        color.h = 19;
        color.s = 98;
        color.v = 83;
        return (color);
    }
    color.h = 33;
    color.s = i;                
    color.v = 100;
    return (color);
*/
}
t_hsv julia(t_complex z, t_complex c, data_str *env, int iteration_max)
{
    int i;
    t_hsv color;
    i = 0;

    for (i = 0; i < iteration_max && get_complex_size(z) < 4; i++)
    {
        z = add_comp(square_comp(z), get_complex(-0.8, 0.2));
    }

    if (i == iteration_max)
    {
        color.h = 0;
        color.s = 0;
        color.v = 0;
        return (color);
    }
    color.h = 240;
    color.s = i;                
    color.v = 100;
    return (color);
}

double pix_calc(data_str *env, int p, char is)
{
    double res;
    double z;

    if (is == 'y')
        res = ((2 * ((p + 0.5) / env->size_y)) - 1) * env->mlx_img->ZOOM + env->mlx_img->START_Y;
    else
        res = ((3.5 * ((p + 0.5) / env->size_x)) - 2) * env->mlx_img->ZOOM + env->mlx_img->START_X;
    if ((env->size_x / env->size_y) < 1)
	{
		z = env->size_y / env->size_x;
		if (is == 'y')
			return (z * res);
		else
			return (res);
	}
	else
	{
		z = env->size_x / env->size_y;
		if (is == 'x')
			return (z * res);
		else
			return (res);
	}
    return (res); 
}

void print_fract(data_str *env)
{
        clock_t start, stop;
       // Tableau temporaire pour une ligne de pixels
    unsigned char line_buffer[env->size_x * 3];

        unsigned char color[3];

        double Cx,Cy;
		const double CxMin= env->CxMin;
        const double CxMax= env->CxMax;
        const double CyMin= env->CyMin;
        const double CyMax= env->CyMax;

        int iX,iY;
        t_hsv hsv;
        hsv.s = 71;
        hsv.v = 90;
        double Zx, Zy;
        double Zx2, Zy2; 
        double PixelWidth=(CxMax-CxMin)/env->size_x;
        double PixelHeight=(CyMax-CyMin)/env->size_y;
        int i;
        for( iY = 0;iY<env->size_y;iY++)
        {
            Cy = pix_calc(env, iY, 'y');
             for(iX=0;iX<env->size_x;iX++)
             {       
                 Cx = pix_calc(env, iX, 'x');
                        px_to_onscreenimg(env, iX, iY, hsv_to_rgb(mandelbrot(get_complex(Cx, Cy), get_complex(Cx, Cy), env, env->iterations)));
            }
        }
        mlx_put_image_to_window(env->mlx_ptr, env->mlx_win, env->mlx_img->img_ptr, 0, 0);

}

int keyboard_hook(int keycode,data_str *env)
{
    printf("%d\n", keycode);
    if(keycode == 6)
    {
        env->mlx_img->ZOOM += 0.1;
    }
    if(keycode == 36)
    {
        env->iterations += 100;
    }
    print_fract(env);
    return 1;
}

int mouse_hook(int button,int x,int y,data_str *env){
   // printf("button : %d | x : %d | y : %d\n", button, x, y);
   // printf("startX : %f | startY : %f\n", env->mlx_img->START_X, env->mlx_img->START_Y);
    if (button == 1)
        {
        env->mlx_img->START_X = pix_calc(env, x, 'x');
		env->mlx_img->START_Y = pix_calc(env, y, 'y');
        env->mlx_img->ZOOM *= ( 0.9);
        // env->mlx_img->START_Y += (y / env->size_y) / env->mlx_img->ZOOM;
        // env->mlx_img->START_X += (x / env->size_x) / env->mlx_img->ZOOM;
        printf("%f\n", env->mlx_img->ZOOM);
        env->mousex = x;
        env->mousey = y;
        }
    if (button == 5)
    {
        env->mlx_img->ZOOM /= 1.1;
        env->mousex = x;
        env->mousey = y;
       // env->mlx_img->START_X = x;
        //env->mlx_img->START_Y = y;
    }
    if (button == 1)
    {
        env->test += 1;
        
    }
    print_fract(env);
    return (1);
}

int main()
{
    data_str *env;
    void *param;
    int count_h, count_w;
    count_h = -1;
    char *str;
    if (!(env = malloc(sizeof(data_str))))
		return (0);
    if (!(env->mlx_img = malloc(sizeof(t_img))))
		return (0);
    env->size_x = 1280;
    env->size_y = 720;
    env->mlx_img->START_X = 0;
    env->mlx_img->START_Y = 0.0;
    env->mlx_img->ZOOM = 0.99;
    env->mousex = 0;
    env->mousey = 0;
    env->CxMin = -2.5;
    env->CxMax = 1.5;
    env->CyMin = -1.5;
    env->CyMax = 2;
    env->iterations = 100;
    env->mlx_ptr = mlx_init();
    env->mlx_win = mlx_new_window(env->mlx_ptr, env->size_x, env->size_y, "new Window");
    //px_put(env, 9845840);
    env->mlx_img->img_ptr = mlx_new_image(env->mlx_ptr , env->size_x, env->size_y);
    env->mlx_img->data = (char *)mlx_get_data_addr(env->mlx_img->img_ptr, &env->mlx_img->bpp, &env->mlx_img->size_l,
		&env->mlx_img->endian);
    printf("bpp %d, size %d\n", env->mlx_img->bpp, env->mlx_img->size_l);
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
				
				env->mlx_img.data[count_h * 1920 + count_w] = 0xFFFFFF;
			else
				env->mlx_img.data[count_h * 1920 + count_w] = 0;
		}
	}*/
    print_fract(env);
    mlx_put_image_to_window(env->mlx_ptr, env->mlx_win, env->mlx_img->img_ptr, 0, 0);

    //str = get_xpm("test.xpm");
    //printf("%s\n", str);
    //printf("%lu\n", strlen(str)); 
    mlx_mouse_hook(env->mlx_win, mouse_hook, env);
    mlx_key_hook(env->mlx_win, keyboard_hook, env);
    mlx_loop(env->mlx_ptr);
    return (1);
}
