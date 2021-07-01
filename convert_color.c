#include "fractole.h"

int	get_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	int			result;

	result = r;
	result = (result << 8) + g;
	result = (result << 8) + b;
	return (result);
}
int	rgb_to_int(t_rgb rgb)
{
	return (get_rgb(rgb.r, rgb.g, rgb.b));
}
t_rgb			int_to_rgb(int c)
{
	t_rgb		rgb;

	rgb.r = c >> 16;
	rgb.g = (c >> 8) - ((c >> 16) * 0x100);
	rgb.b = c - ((c >> 8) * 0x100);
	return (rgb);
}

int	hsv_to_rgb(t_hsv hsv)
{
	float	c;
	float	h;
	float	x;
	float	m;

	c = (float)hsv.v / 100 * ((float)hsv.s / 100);
	h = (float)hsv.h / 60;
	x = c * (1 - fabsf(h - ((int)h / 2 * 2) - 1));
	m = (float)hsv.v / 100 - c;
	if (h >= 0 && h < 1)
		return (get_rgb(round((c + m) * 255), round((x + m) * 255), round(m * 255)));
	if (h >= 1 && h < 2)
		return (get_rgb(round((x + m) * 255), round((c + m) * 255), round(m * 255)));
	if (h >= 2 && h < 3)
		return (get_rgb(round(m * 255), round((c + m) * 255), round((x + m) * 255)));
	if (h >= 3 && h < 4)
		return (get_rgb(round(m * 255), round((x + m) * 255), round((c + m) * 255)));
	if (h >= 4 && h < 5)
		return (get_rgb(round((x + m) * 255), round(m * 255), round((c + m) * 255)));
	return (get_rgb(round((c + m) * 255), round(m * 255), round((x + m) * 255)));
}

void px_to_onscreenimg(data_str *data_strc , int x, int y, int c)
{
	data_strc->mlx_img->data[x * 4 + y * data_strc->size_x * 4] = int_to_rgb(c).b;
	data_strc->mlx_img->data[x * 4 + y * data_strc->size_x * 4 + 1] = int_to_rgb(c).g;
	data_strc->mlx_img->data[x * 4 + y * data_strc->size_x * 4 + 2] = int_to_rgb(c).r;
	data_strc->mlx_img->data[x * 4 + y * data_strc->size_x * 4 + 3] = 0;
}
