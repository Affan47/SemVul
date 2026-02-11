my_numbox_check_minmax(t_my_numbox *x, double min, double max)
{
    int ret=0;

    if(x->x_lin0_log1)
    {
        if((min == 0.0)&&(max == 0.0))
            max = 1.0;
        if(max > 0.0)
        {
            if(min <= 0.0)
                min = 0.01*max;
        }
        else
        {
            if(min > 0.0)
                max = 0.01*min;
        }
    }
    x->x_min = min;
    x->x_max = max;
    if(x->x_val < x->x_min)
    {
        x->x_val = x->x_min;
        ret = 1;
    }
    if(x->x_val > x->x_max)
    {
        x->x_val = x->x_max;
        ret = 1;
    }
    if(x->x_lin0_log1)
        x->x_k = exp(log(x->x_max/x->x_min)/(double)(x->x_log_height));
    else
        x->x_k = 1.0;
    return(ret);
}
