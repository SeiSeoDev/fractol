#include "fractole.h"
t_complex add_comp(t_complex a, t_complex b)
{
    t_complex result;
 
    result.r = a.r + b.r;
    result.i = a.i + b.i;
    return (result);
}

t_complex square_comp(t_complex a)
{
    t_complex result;
    float   tmp;

    tmp = a.r;
    result.r = a.r * a.r - a.i * a.i;
    result.i = 2 * tmp * a.i;
    return (result);
}

t_complex get_complex(float x, float y)
{
    t_complex result;
    
    result.r = x;
    result.i = y;
    return (result);
}

float get_complex_size(t_complex a)
{
    return (fabs(a.r * a.r) + fabs(a.i * a.i));
}