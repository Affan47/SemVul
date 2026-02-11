metro_tick(t_metro *x)
{
    x->x_hit = 0;
    outlet_bang(x->x_obj.ob_outlet);
    if (!x->x_hit) clock_delay(x->x_clock, x->x_deltime);
}
